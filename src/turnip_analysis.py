import matplotlib.pyplot as plt
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.base import MIMEBase
from email import encoders
    
def send_graph():
    '''Sends gmail to people'''
    email_user = 'python.bot.3.6.4@gmail.com'
    email_password = 'PythonBot123'
    email_send = 'escobedo001@gmail.com'
    subject = 'Animal Crossing Turnip Prices Graph'

    msg = MIMEMultipart()
    msg['From'] = email_user
    msg['To'] = email_send
    msg['Subject'] = subject

    body = 'Prices'
    msg.attach(MIMEText(body,'plain'))

    filename = 'Animal Crossing Turnip Prices.png'
    attachment = open(filename,'rb')

    times = 1

    part = MIMEBase('application','octet-stream')
    part.set_payload((attachment).read())
    encoders.encode_base64(part)
    part.add_header('Content-Disposition',"attachment; filename= "+filename)

    msg.attach(part)
    text = msg.as_string()
    server = smtplib.SMTP('smtp.gmail.com',587)
    server.starttls()
    server.login(email_user,email_password)

    for i in range(times):
        server.sendmail(email_user,email_send,text)
    
    server.quit()

def turnip_graph() -> None:
    '''Shows the graph'''
    data_file = open('turnip_prices.txt', 'r')
    days = []
    morning = []
    noon = []
    
    for line in data_file:
        line = line.split(',')
        days.append(int(line[0]))
        morning.append(int(line[1]))
        noon.append(int(line[2]))

    data_file.close()
        
    #plt.plot(days, morning, color='blue', label='Morning Price')
    plt.plot(days, noon, color='red', label = 'Afternoon Price')
    plt.xlabel('Day')
    plt.xticks(range(1,len(days)+1))
    plt.ylabel('Bells')
    plt.yticks(range(min(noon), max(noon)+7, 7))
    #plt.yticks(range(min(morning+noon), max(morning+noon)+1, 7))
    plt.title('Animal Crossing Turnip Prices')
    plt.grid()
    plt.legend()
    plt.savefig('Animal Crossing Turnip Prices.png')
    plt.show()
    

def day_price(day:str) -> None:
    '''Shows scatterplot for a day's prices'''
    data_file = open('turnip_prices.txt', 'r')
    morning = []
    noon = []
    
    for line in data_file:
        line = line.strip().split(',')
        if line[3] == day:
            morning.append(int(line[1]))
            noon.append(int(line[2]))

    data_file.close()

    days = [x for x in range(1, len(morning)+1)]

    plt.plot(days,morning, color = 'blue', label = 'Morning Price')
    plt.plot(days, noon, color = 'red', label = 'Noon Price')
    plt.xlabel('Day')
    plt.xticks(range(1,len(days)+1))
    plt.ylabel('Bells')
    plt.yticks(range(min(morning+noon), max(morning+noon)+1))
    plt.title('{} Turnip Prices'.format(day))
    plt.grid()
    plt.show()
    
    
if __name__ == '__main__':
    turnip_graph()
    #send_graph()
