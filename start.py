import pyautogui, time, pygetwindow, PIL, cv2, os, math, operator, time, random
import numpy as np 
from functools import reduce
from PIL import ImageOps
from copy import deepcopy
import subprocess

MOUSE_SPEED = .4 #seconds

DEPTH = 3

windows = pygetwindow.getAllTitles()

ppWindow = None
for i in range(len(windows)):
	if "Puzzle Pirates" in windows[i]:
		ppWindow = windows[i]

templates = []
names = []
path, dirs, files = next(os.walk('./images'))
for file in files:
	templates.append(PIL.Image.open('./images/' + file).resize((90,90)))
	names.append(file)

pieces = {
	'darkblue_square.png': 1,
	'greenblue_diamond.png': 2,
	'lightblue_circle.png': 3,
	'lightblue_diamond.png' : 4,
	'lightblue_square.png' : 5,
	'lightyellow_circle.png' : 6,
	'whiteblue_square.png' : 7,
	'jellyfish.png' : "J",
	'puffer.png': "P",
	'crab.png': "C"
}

def mod1(num):
	if (num > 0):
		return num % 1
	else:
		return ((num*-1) % 1) * -1

def mouse_glide_to(x,y):
    """Smooth glides mouse from current position to point x,y with default timing and speed"""
    x1,y1 = pyautogui.position()
    smooth_glide_mouse(x1,y1, x, y, MOUSE_SPEED, 50)
 
def smooth_glide_mouse(x1,y1,x2,y2, t, intervals):
    """Smoothly glides mouse from x1,y1, to x2,y2 in time t using intervals amount of intervals"""
    distance_x = x2-x1
    distance_y = y2-y1

    intervalOveragex = 0
    intervalOveragey = 0

    currx = x1
    curry = y1
    for n in range(0, intervals+1):
        overagex = mod1(distance_x/intervals)
        overagey = mod1(distance_y/intervals)

        intervalOveragey += overagey
        intervalOveragex += overagex

        addX = 0
        addY = 0

        if (abs(intervalOveragey) >= 1):
        	if (intervalOveragey > 0):
        		addY = 1
        	else:
        		addY = -1
        	intervalOveragey = mod1(intervalOveragey)
        if (abs(intervalOveragex) >= 1):
        	if (intervalOveragex > 0):
        		addX = 1
        	else:
        		addX = -1
        	intervalOveragex = mod1(intervalOveragex)

        #print(distance_y/intervals,(distance_y/intervals) + addY)

        currx += int((distance_x/intervals) + addX)
        curry += int((distance_y/intervals) + addY)
        #print(distance_x, distance_y, currx, curry,flush=True)
        pyautogui.moveTo(currx,curry, _pause=False)
        #move_mouse(x1 + n * int((distance_x/intervals) + addX), y1 + n * int((distance_y/intervals) + addY))
        #time.sleep(t*1.0/intervals)


def printBoard(board):
	for i in range(len(board)):
		print(board[i])

def checkWeirdTiles(board):
	for i in range(len(board)):
		for j in range(len(board[i])):
			if board[i][j] in ['J' , 'P']:
				return [i,j]
	return False

def bestPlay(board, ppCords, test=False):
	print(' ')
	check = checkWeirdTiles(board)

	obj = {
		'board': board,
		'previous': [],
		'best': 0,
		'broke': False
	}

	bestMove = []
	if (not check):
		## send of c++ program
		with open("data.txt", "w") as file1:
			for i in range(len(board)):
				for j in range(len(board[0])):
					file1.write(str(board[i][j]) +  " ")
		subprocess.call(["./a.out"])
		with open('moves.txt') as f:
			lines = f.readlines()
			bestMove = [{
				'previous': []
			}]
			for i in range(0, len(lines), 2):
				arr = []
				arr.append(int(lines[i].strip()))
				arr.append(int(lines[i+1].strip()))
				# print(arr)
				bestMove[0]['previous'].append(arr)


		if (len(bestMove[0]['previous']) == 0):
			row = random.randint(0,5)
			col = random.randint(0,11)
			print('Doing random move nothing good atm.')
			if (not test):
				mouse_glide_to(ppCords[0] + 116 + row*45 + random.randint(5,10) , ppCords[1] + 87 + col*45 + random.randint(-5,5))
				pyautogui.click()	
		else:
			print('Performing moves: ' + str(bestMove[0]['previous']))
			if (not test):
				print('')
				for i in range(len(bestMove[0]['previous'])):
					mouse_glide_to(ppCords[0] + 116 + bestMove[0]['previous'][i][1]*45 + random.randint(5,10) , ppCords[1] + 87 + bestMove[0]['previous'][i][0]*45 + random.randint(-5,5))
					pyautogui.click()
					time.sleep(.25)
				time.sleep(.75)
		# print(bestMove)
		# for i in range(DEPTH):
		# 	if (len(bestMove) == 0):
		# 		bestMove = getPlaysCurrentBoard(obj.copy(), i)
		# 	else:
		# 		for j in range(len(bestMove)):
		# 			if (bestMove[j]['broke'] == False):
		# 				newMoves = getPlaysCurrentBoard(bestMove[j].copy(), i)
		# 				bestMove += newMoves
	else:
		bestMove = [{
			'previous': [check]
		}]
		print('jellyfish or pufferfish best is message is placeholder')
		if (not test and bestMove[0]['previous'][0][0] != 0):
			for i in range(len(bestMove[0]['previous'])):
				mouse_glide_to(ppCords[0] + 116 + bestMove[0]['previous'][i][1]*45 + random.randint(5,10) , ppCords[1] + 87 + bestMove[0]['previous'][i][0]*45 + random.randint(-5,5))
				pyautogui.click()
				time.sleep(.25)
				return
	# for i in range(len(bestMove)):
	# 	if (bestMove[i]['best'] >= 3):
	# 		print(bestMove[i])
			#printBoard(bestMove[i]['board'])





	# bestMove = sorted(bestMove, key=lambda x: x['best'], reverse=True)[0]
	# best = bestMove['best']
	# if (best == 0):
	# 	best = 1
	# 	row = random.randint(0,5)
	# 	col = random.randint(0,11)
	# 	print('Doing random move nothing good atm.')
	# 	if (not test):
	# 		mouse_glide_to(ppCords[0] + 116 + row*45 + random.randint(5,10) , ppCords[1] + 87 + col*45 + random.randint(-5,5))
	# 		pyautogui.click()		
	# 	return 
	# if (best > 10 or (bestMove['previous'][0] == [0,3] and check) or (bestMove['previous'][0] == [0,0] and check)):
	# 	print('Skipping.')
	# 	time.sleep(0.5)
	# 	return
	# if (best):
	# 	print('Doing move that gives ' + str(best) +' points.' , bestMove['previous'])
	# 	# printBoard(board)
	# 	# print('')
	# 	# printBoard(board_cp)	
	# 	if (not test):
	# 		for i in range(len(bestMove['previous'])):
	# 			mouse_glide_to(ppCords[0] + 116 + bestMove['previous'][i][1]*45 + random.randint(5,10) , ppCords[1] + 87 + bestMove['previous'][i][0]*45 + random.randint(-5,5))
	# 			pyautogui.click()
	# 			time.sleep(1.0)


def getPlaysCurrentBoard(obj, depth):
	board = obj['board']
	previousMovess = obj['previous']
	potentialMoves = []
	best = obj['best']
	rangey = [0, len(board)]
	rangex = [0, len(board[0])-1]
	if (previousMovess):
		yyrange = previousMovess[-1][0]
		xxrange = previousMovess[-1][1]
		xxrange = [0 if xxrange - 3 < 0 else xxrange -3, 5 if xxrange + 3 > 5 else xxrange + 3]
		yyrange = [0 if yyrange - 3 < 0 else yyrange -3, 11 if yyrange + 3 > 11 else yyrange + 3]
		rangey = yyrange
		rangex = xxrange
	if (depth > 0):
		best -=1
	for i in range(rangey[0], rangey[1], 1):
		for j in range(rangex[0], rangex[1], 1):
			board_cp = deepcopy(board)
			temp = board_cp[i][j]
			board_cp[i][j] = board_cp[i][j+1]
			board_cp[i][j+1] = temp
			x = evalBoard(board_cp)
			broke = False if x == 0 else True
			previousMoves = deepcopy(previousMovess)
			previousMoves.append([i,j])
			potentialMoves.append({
				'board': board_cp,
				'previous': previousMoves,
				'best': x + best,
				'broke': broke
			})

	return potentialMoves

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
	return total


def main(test = False):
	while(True):
		ppCords = []

		if (not test):

			x1, y1, width, height = pygetwindow.getWindowGeometry(ppWindow)
			ppCords = pygetwindow.getWindowGeometry(ppWindow)
			im = pyautogui.screenshot(region = (x1*2,y1*2,width*2,height*2))
			## im.save('./pics/board.png')

		if (test):
			#im.save('./pics/board.png')
			im = PIL.Image.open('./pics/board.png')


		x = 179 - 90
		y = 135 - 90

		board = []
		for i in range(12):
			y += 90
			row = []
			row2 = []
			x = 179-90
			for k in range(6):
				x +=90
				im_crop = im.crop((x,y,x+90,y+90))
				im_crop.convert('RGB')
				# im_crop.save('./pics/boardcrop.png', quality=100)
				piece = None
				largest = -10000
				maxTotal = 0
				for j in range (len(templates)):
					#img = cv2.imread('./pics/boardcrop.png')
					img = cv2.cvtColor(np.array(im_crop), cv2.COLOR_RGB2BGR)
					res = cv2.matchTemplate(img, cv2.resize(cv2.imread('./images/' + names[j]), dsize=(90, 90)), cv2.TM_CCOEFF_NORMED)
					min_val, max_val, min_loc, max_loc = cv2.minMaxLoc(res)
					maxTotal += max_val
					if max_val > largest:
						piece = pieces[names[j]]
						largest = max_val


					# # diff = rmsdiff(ImageOps.grayscale(im_crop),ImageOps.grayscale(templates[j]))
					# diff = rmsdiff(im_crop, templates[j])
					# #print(diff, j, names[j])
					# if diff < smallest:
					# 	piece = pieces[names[j]]
					# 	smallest = diff
				row.append(piece)
			board.append(row)
		# if (maxTotal< 240):
		# 	time.sleep(1.5)
		# 	print('Probably not bilging')
		# 	continue
		bestPlay(board, ppCords, test=test)
		time.sleep(0.5)
		if (test):
			quit()

main(test=False)









