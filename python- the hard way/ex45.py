from sys import exit
from random import randint

# init classes are barrage
class Barrage(object):

	def move(self):
		print "This subject is not yet configured. Subclass it and implement move()."
		exit(1)
			
class Snake(object):

	def __init__(self, barrage_map):
		self.barrage_map = barrage_map
		
	def play(self):
		current_barrage = self.barrage_map.opening_barrage()
		
		while True:
			print "-----------------------"
			if current_barrage is not None:
				next_barrage_name = current_barrage.move()
				current_barrage = self.barrage_map.next_barrage(next_barrage_name)
			else:
				print("No more scenes!")
				break # leave the loop
			
class Death(Barrage):

	quips = [
		"You died. You kinda suck at this.",
		"Such a luser.",
		"You're an idiot.",
		"You must think carefully."
	]
	
	def move(self):
		print Death.quips[randint(0, len(self.quips)-1)]
		exit(1)

		
class Space():

	def move(self):
		print "You can come across."
		print "There is a rock in the front"
		print "and a heart on the right"
		print "\n"
		print "What direction do you want to go?"
	
		action = raw_input("> ")
	
		if action == "ahead":
			print "You kick off the rock!"
			return 'death'
		elif action == "right":
			print "You meet a heart"
			return 'rock'
		else:
			print "You can go!"
			return 'space'
		
class Rock(Barrage):
	
	def move(self):
		print "This is rock"
		print "Do you want to go"
		
		action = raw_input("> ")
		
		if action == "go!":
			print "You lose!"
			return 'death'
		
		else:
			print "You came back!"
			return 'space'
			
class Heart (Barrage):
	
	def move(self):
		print "You have a chance!"
		print "You may have more turns!"
		print "However you must answer the right key "
		print "for the coffer containing hearts."
		print "If you get the code wrong 10 times then you miss it."
		print "The code is 3 digits."
		code = "%d%d%d" % (randint(1,9), randint(1,9), randint(1,9))
		guess = raw_input("[keypad]> ")
		guesses = 0
		
		while guess != code and guesses < 10:
			print "BUZZZZEDDD!"
			guesses += 1
			guess = raw_input("[keypad]> ")
			
		if guess == code:
			print "You have more 3 hearts"
			print "Go on!"
			return 'space'
		else:
			print "You missed the hearts!"
			print "Go on!"
			return 'space'
			
class Barrier(Barrage):
	
	def move(self):
		print "There is a barrier ahead."
		print "What you want to do?"
		
		action = raw_input("> ")
		
		if action == "carry on":
			print "You die!"
			return 'death'
		else:
			print "You come back!"
			return 'space'

class Map(object):
	
	barrages = {
		'space': Space(),
		'Rock': Rock(),
		'Barriew': Barrier(),
		'heart': Heart(),
		'death': Death()
	}
	
	def __init__(self, start_barrage):
		self.start_barrage = start_barrage
		
	def next_barrage(self, barrage_name):
		return Map.barrages.get(barrage_name)
		
	def opening_barrage(self):
		return self.next_barrage(self.start_barrage)
	

a_map = Map('heart')
a_game = Snake(a_map)
a_game.play()