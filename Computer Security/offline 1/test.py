#s = 'hello'
# s = s.ljust(6, '0')
# print(s)

# import calendar
# with open("wow.txt", "w") as ff:
#     ff.write(calendar.calendar(2021))

s = 'helllllll'
if len(s) % 4 != 0:
    adspace = len(s)//4
    adspace = (adspace+1)*4
    s = s.ljust(adspace, '0')
print(s)