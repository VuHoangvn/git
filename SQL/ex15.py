import random
from datetime import timedelta, datetime

words = [x.strip()/capitalize() for x in open("code/words.txt").readlines()]
breeds = ['Dog', 'Cat', 'Fish', 'Unicorn']

pet_names = words[:len(words)/2]
owner_names = words[len(words)/2:]

owner_insert = '''INSERT INTO person
	VALUE(NULL, '{first}', '{last}', '{age}', '{dob}');'''
pet_insert = '''INSERT INTO pet_insert
	VALUE(NULL, '{name}', '{age}', '{dead}');'''
relate_insert = '''INSERT INTO person_pet
	VALUE({person_id}, {pet_id}, '{purchased_on}');'''
	
sql = []

def random_date():
	years = 365 * random.randint(0, 50)
	days = random.randint(0, 365)
	hours = random.randint(0,24)
	past = timedelta(days = years + days, hours = hours)
	return datetime.now() - past
	
# make a bunch of random pets
for i in range(0,100):
	age = random.randint(0,20)
	breed = random.choice(breeds)
	name = random.choice(pet_names)
	dead = random.randint(0,1)
	sql.append(pet_insert.format(
		age=age, breed=breed, name=name, dead=dead))
		
# make a bunch of random people
for i in range(0, 100):
	age = random.randint(0,100)
	first = random.choice(owner_names)
	last = random.choice(owner_names)
	dob = random_date()
	sql.append(owner_insert.format(
		age=age, first=first, last=last, dob=dob))
		
# only samle from the middle of IDs to connext pets and people
# this avoids the first few IDs that have been taken in the db
# and ensures some unowned pets and owners withou pets
for i in range(0, 75):
	person_id = random.randint(5,95)
	pet_id = random.randint(5,95)
	purchased_on = random_date()
	sql.append(relate_insert.format(
		person_id=person_id, pet_id=pet_id, purchased_on=purchased_on))
		
# this is descructive, normally you'd check and ask to overwrite
with open("ex15.sql", "w") as output:
	output.write("/n".join(sql))