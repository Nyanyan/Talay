import serial
import serial.tools.list_ports
import os
import tkinter
import openpyxl

def search_com_port():
    coms = serial.tools.list_ports.comports()
    comlist = []
    for com in coms:
        comlist.append(com.device)
    print('Connected COM ports: ' + str(comlist))
    use_port = comlist[0]
    print('Use COM port: ' + use_port)
    return use_port

def nameinput(n):
    global maxrow
    row = maxrow + 1
    if n == 1:
        row += 1
    name = namebox.get()
    sheet.cell(row=row, column=1, value=name)
    namebox.config(state = 'disable')
    nameentbutton.config(state = 'disable')

def timeinput(turn, n):
    global maxrow
    row = maxrow + 1
    if n == 1:
        row += 1
    sheet.cell(row=row, column=turn + 2, value=time[n][turn])
    wb.save('test.xlsx')
    if n == 0:
        if turn == 0:
            t10box.config(state='disable')
            t10entbutton.config(state='disable')
        if turn == 1:
            t20box.config(state='disable')
            t20entbutton.config(state='disable')
        if turn == 2:
            t30box.config(state='disable')
            t30entbutton.config(state='disable')
        if turn == 3:
            t40box.config(state='disable')
            t40entbutton.config(state='disable')
        if turn == 4:
            t50box.config(state='disable')
            t50entbutton.config(state='disable')
    print('done')


def confirmtime():
    t10box.delete(0, tkinter.END)
    t10box.insert(tkinter.END,time[0][0])
    t20box.delete(0, tkinter.END)
    t20box.insert(tkinter.END,time[0][1])
    t30box.delete(0, tkinter.END)
    t30box.insert(tkinter.END,time[0][2])
    t40box.delete(0, tkinter.END)
    t40box.insert(tkinter.END,time[0][3])
    t50box.delete(0, tkinter.END)
    t50box.insert(tkinter.END,time[0][4])

def inputserial():
    global time, turn
    ser = serial.Serial()
    ser.port = port
    ser.baundrate = 9600
    ser.timeout = 0.1 #sec
    ser.setDTR(False)
    ser.open()

    line = ser.readline().decode('utf8', 'ignore').rstrip(os.linesep)
    if line != '':
        #print(line)
        f = False
        arr = ['0','1']
        if line[0] in arr:
            if len(line) == 10:
                checksum = 64
                for j in range(6):
                    tmp = ['0','1','2','3','4','5','6','7','8','9']
                    if line[j + 3] in tmp:
                        checksum += int(line[j + 3])
                    else:
                        checksum = 0
                        break
                if chr(checksum) == line[9]:
                    f = True
                    num = int(line[0])
                    minute = int(line[3])
                    second = int(line[4]) * 10 + int(line[5])
                    msecond = int(line[6]) * 100 + int(line[7]) * 10 + int(line[8])
                    #print(num,minute,second,msecond)
                    time[int(line[0])][turn[int(line[0])]] = str(minute * 60 + second) + '.' + str(msecond) #str(minute) + ':' + str(second) + '.' + str(msecond)
                    print(time[int(line[0])][turn[int(line[0])]])
                    turn[int(line[0])] += 1
                    confirmtime()
                    f = True
                else:
                    f = False
        if f:
            for i in range(30):
                ser.write('y'.encode())
    
    ser.close()
    root.after(1,inputserial)

port = search_com_port()

wb = openpyxl.load_workbook('test.xlsx')
sheet = wb['Sheet1']
maxcol = sheet.max_column
maxrow = sheet.max_row

time = []
for i in range(2):
    time.append([])
    for j in range(5):
        time[i].append('')
turn = [0, 0]

root = tkinter.Tk()
root.title("Talay1.0")
root.geometry("500x900")
canvas = tkinter.Canvas(root, width = 500, height = 900)
canvas.place(x=0,y=0)

namelabel = tkinter.Label(root, text='Name')
namelabel.grid(row=0, column=0, padx=5, pady=5)
namebox = tkinter.Entry(width=50)
namebox.grid(row=0, column=1, padx=5, pady=5)
nameentbutton = tkinter.Button(root, text='Confirm', command=lambda :nameinput(0))
nameentbutton.grid(row=0, column=2, padx=5, pady=5)

t10label = tkinter.Label(root, text='T1')
t10label.grid(row=1, column=0, padx=5, pady=5)
t10box = tkinter.Entry(width=50)
t10box.grid(row=1, column=1, padx=5, pady=5)
t10entbutton = tkinter.Button(root, text='Confirm', command=lambda :timeinput(0, 0))
t10entbutton.grid(row=1, column=2, padx=5, pady=5)

t20label = tkinter.Label(root, text='T2')
t20label.grid(row=2, column=0, padx=5, pady=5)
t20box = tkinter.Entry(width=50)
t20box.grid(row=2, column=1, padx=5, pady=5)
t20entbutton = tkinter.Button(root, text='Confirm', command=lambda :timeinput(1, 0))
t20entbutton.grid(row=2, column=2, padx=5, pady=5)

t30label = tkinter.Label(root, text='T3')
t30label.grid(row=3, column=0, padx=5, pady=5)
t30box = tkinter.Entry(width=50)
t30box.grid(row=3, column=1, padx=5, pady=5)
t30entbutton = tkinter.Button(root, text='Confirm', command=lambda :timeinput(2, 0))
t30entbutton.grid(row=3, column=2, padx=5, pady=5)

t40label = tkinter.Label(root, text='T4')
t40label.grid(row=4, column=0, padx=5, pady=5)
t40box = tkinter.Entry(width=50)
t40box.grid(row=4, column=1, padx=5, pady=5)
t40entbutton = tkinter.Button(root, text='Confirm', command=lambda :timeinput(3, 0))
t40entbutton.grid(row=4, column=2, padx=5, pady=5)

t50label = tkinter.Label(root, text='T5')
t50label.grid(row=5, column=0, padx=5, pady=5)
t50box = tkinter.Entry(width=50)
t50box.grid(row=5, column=1, padx=5, pady=5)
t50entbutton = tkinter.Button(root, text='Confirm', command=lambda :timeinput(4, 0))
t50entbutton.grid(row=5, column=2, padx=5, pady=5)

root.after(1,inputserial)
root.mainloop()