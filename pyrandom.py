import random 

# with open("data.txt", "w") as file1:
# 	for i in range():
# 		for j in range(len(board[0])):
# 			file1.write(str(board[i][j]) +  " ")

def printBoard(board):
	for i in range(len(board)):
		print(board[i])

def evalBoard(board):
	total = 0
	for i in range(len(board)):
		tilePrev = None
		counter = 0
		for j in range(len(board[i])):
			tile = board[i][j]
			if (tile == tilePrev and j == (len(board[i])-1)):
				counter +=1
				if (counter >= 2):
					if (total >= 3):
						total += 5
					elif (total >= 1):
						total +=3
					else:
						total +=1		
			elif (tile == tilePrev):
				counter +=1
			else: 
				if (counter >= 2):
					if (total >= 3):
						total += 5
					elif (total >= 1):
						total +=3
					else:
						total +=1					
				counter = 0
			tilePrev = tile
	for i in range(len(board[0])):
		tilePrev = None
		counter = 0
		for j in range(len(board)):
			tile = board[j][i]
			if (tile == tilePrev and  j == (len(board)-1)):
				counter +=1
				if (counter >= 2):
					# x('hi', i, j, total)
					if (total >= 3):
						total += 5
					elif (total >= 1):
						total +=3
					else:
						total +=1		
			elif (tile == tilePrev):
				counter +=1
			else: 
				if (counter >= 2):
					# print('hi2', i, j, total)
					# printBoard(board)
					if (total >= 3):
						total += 5
					elif (total >= 1):
						total +=3
					else:
						total +=1					
				counter = 0		
			tilePrev = tile	
	return total > 0

while(True):
	y = []
	for i in range(12):
		y.append([])
	for i in range(len(y)):
		for j in range(6):
			y[i].append(random.randint(1,7))
	printBoard(y)
	if (evalBoard(y)):
		print("saw combo continuing")
		continue
	with open("data.txt", "w") as file1:
		for i in range(len(y)):
			for j in range(len(y[0])):
				file1.write(str(y[i][j]) +  " ")	
	break
