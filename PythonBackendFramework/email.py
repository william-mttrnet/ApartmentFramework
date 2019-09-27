import smtplib
import time
import imaplib
import email

# Gmail defaults 
SMTP_SERVER = "imap.gmail.com"
SMTP_PORT   = 993

class EmailHandler():
    def __init__(self, username, password):
        # sensitive user data. 
        self.username = username 
        self.password = password

        # Mail handle.
        self.mail = None

        # Mail ID information.
        self.mail_ids = None
        self.id_list = None
        
    def connect(self):
        self.mail = imaplib.IMAP4_SSL(SMTP_SERVER)
        self.mail.login(self.username, self.password)
        self.mail.select('inbox')
        return True

    def fetch_mail(self):
        type, data = self.mail.search(None, 'ALL')
        self.mail_ids = data[0]
        self.id_list = self.mail_ids.split()
        
        for mail in self.id_list:
            # Get email by id!
            type, data = self.mail.fetch(mail, 'RFC822') 
            print(data)


# Test code...
email_handler = None
def main():
    print("Creating email handler...")
    global email_handler
    email_handler = EmailHandler("tinanh1@uci.edu", "saphannie1s.")

    if(email_handler.connect()):
        print("Mailbox connected!")
    
    email_handler.fetch_mail()
main()
