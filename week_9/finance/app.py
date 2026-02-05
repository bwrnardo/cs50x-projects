import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    rows = db.execute(
        "SELECT symbol, SUM(shares) as shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", session["user_id"])

    total_value = 0
    for row in rows:
        quote = lookup(row["symbol"])
        if quote != None:
            row["name"] = quote["name"]
            row["price"] = quote["price"]
            row["total"] = quote["price"] * row["shares"]
            total_value += row["total"]
        else:
            row["name"] = "N/A"
            row["price"] = 0
            row["total"] = 0

    user_db = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

    total_value += user_db[0]["cash"]

    return render_template("index.html", stocks=rows, cash=user_db[0]["cash"], total=total_value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")

        shares_input = request.form.get("shares")

        if not symbol:
            return apology("Must provide symbol")

        symbol = symbol.upper()

        if not shares_input:
            return apology("Must provide shares")

        try:
            shares = int(shares_input)
            if shares < 1:
                return apology("Insert positive amount of shares")
        except ValueError:
            return apology("Insert right amount of shares")

        quote = lookup(symbol)
        if quote is None:
            return apology("Invalid Symbol")

        price = quote["price"]
        total_cost = price * shares

        # query database for current cash
        rows = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

        # Validation: check if they have enough cash
        cash = rows[0]["cash"]
        if cash < total_cost:
            return apology("Not enough cash")

        new_cash_balance = cash - total_cost

        # Update user's cash with the calculated number
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash_balance, session["user_id"])

        # Add transaction
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
                   session["user_id"], symbol, shares, price)

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute(
        "SELECT symbol, shares, price, timestamp FROM transactions WHERE user_id = ? ORDER BY timestamp DESC", session["user_id"])

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        # Checks if symbol exists
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("Must provide symbol")

        quote = lookup(symbol.upper())

        if quote == None:
            return apology("Invalid Symbol")

        return render_template("quoted.html", quote=quote)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        # Checks if username was inserted
        username = request.form.get("username")
        if not username:
            return apology("Must provide username")

        # Checks if password was inserted
        password = request.form.get("password")
        if not password:
            return apology("Must provide password")

        # Checks if confirmation of password was inserted
        confirmation = request.form.get("confirmation")
        if not confirmation:
            return apology("Password not confirmed, please confirm it")

        # See if passwords match
        if confirmation != password:
            return apology("Passwords do not match")

        hash = generate_password_hash(password)

        # Handles duplicate usernames
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        if rows:
            return apology("Username already exists")

        hash = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)


        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares_input = request.form.get("shares")

        if not symbol:
            return apology("Must provide symbol")

        symbol = symbol.upper()

        if not shares_input:
            return apology("Must provide shares")

        try:
            shares = int(shares_input)
            if shares < 1:
                return apology("shares must be positive")
        except ValueError:
            return apology("shares must be a number")

        portfolio = db.execute(
            "SELECT symbol, SUM(shares) AS shares FROM transactions WHERE user_id = ? GROUP BY symbol", session["user_id"])

        shares_owned = 0
        for stock in portfolio:
            if stock["symbol"] == symbol:
                shares_owned = stock["shares"]
                break

        if shares > shares_owned:
            return apology("Not enough shares")

        quote = lookup(symbol)

        if quote is None:
            return apology("Symbol not found")

        transaction_value = quote["price"] * shares

        user_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        new_cash = user_cash_db[0]["cash"] + transaction_value

        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, session["user_id"])

        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
                   session["user_id"], symbol, -shares, quote["price"])

        return redirect("/")

    else:
        user_symbols = db.execute(
            "SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", session["user_id"])

        return render_template("sell.html", symbols=user_symbols)
