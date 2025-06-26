import smtplib
import sys
import random
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.header import Header

# === Handle CLI arguments ===
if len(sys.argv) != 3:
    print("Usage: python send_email.py <recipient_email> <username>")
    sys.exit(1)

recipient_email = sys.argv[1]
username = sys.argv[2]
reset_code = str(random.randint(100000, 999999))  # 6-digit OTP

# === Email Configuration ===
sender_email = "loedon76@gmail.com"
reply_to_email = "loedon76@gmail.com"  # Can be different if needed
app_password = "gtzr xmql epka pokd"  # Gmail App Password
subject = Header("Reset Your Push Cash Password", "utf-8")

# === Email Body (HTML + Plaintext) ===
plain_text = f"""Hi {username},

We received a request to reset your password for your Push Cash account.

Your reset code is: {reset_code}

If you didn’t request this, you can ignore this email.

- Push Cash Team
"""

html_body = f"""
<html>
<head>
  <style>
    .container {{
      font-family: Arial, sans-serif;
      background-color: #f9f9f9;
      padding: 20px;
      border-radius: 10px;
      max-width: 500px;
      margin: auto;
      border: 1px solid #ddd;
    }}
    .header {{
      font-size: 20px;
      color: #333;
      margin-bottom: 10px;
    }}
    .code {{
      font-size: 24px;
      color: #2a9d8f;
      font-weight: bold;
      background: #e0f7fa;
      padding: 10px 20px;
      border-radius: 8px;
      display: inline-block;
    }}
    .footer {{
      margin-top: 20px;
      font-size: 12px;
      color: #888;
    }}
  </style>
</head>
<body>
  <div class="container">
    <div class="header">Hi {username},</div>
    <p>We received a request to reset your password for your Push Cash account.</p>
    <p>Your reset code is:</p>
    <div class="code">{reset_code}</div>
    <p>If you didn’t request this, you can safely ignore this email.</p>
    <div class="footer">© 2025 Push Cash Inc.</div>
  </div>
</body>
</html>
"""

# === Setup Email Message ===
message = MIMEMultipart("alternative")
message["From"] = Header("Push Cash", "utf-8")
message["To"] = recipient_email
message["Subject"] = subject
message["Reply-To"] = reply_to_email
message["X-Priority"] = "1"  # High priority
message["X-Mailer"] = "PushCashMailer 1.0"

# Attach both plain-text and HTML
message.attach(MIMEText(plain_text, "plain"))
message.attach(MIMEText(html_body, "html"))

# === Send Email ===
try:
    with smtplib.SMTP("smtp.gmail.com", 587) as smtp:
        smtp.starttls()
        smtp.login(sender_email, app_password)
        smtp.sendmail(sender_email, recipient_email, message.as_string())
        print("Reset code sent successfully!")
        print(f"Reset Code: {reset_code}")
except Exception as e:
    print("Failed to send email.")
    print(f"Error: {e}")

# === Save OTP to file ===
try:
    with open("C:/dss/Final_project11/Final_project/otp.txt", "w") as f:
        f.write(reset_code)
        print(f"OTP {reset_code} written to file.")
except Exception as e:
    print(f"Error writing OTP to file: {e}")