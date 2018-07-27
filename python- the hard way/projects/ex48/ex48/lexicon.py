def scan(sentence):
    directions = ['north', 'south', 'east', 
                  'west', 'down', 'up', 'left',
                  'right', 'back']
    verbs = ['go', 'stop', 'kill', 'eat', 'open']
    stop_words = ['the', 'in', 'of', 'from', 'at', 'it']
    nouns = ['door', 'bear', 'princess', 'cabinet']

    sentence_as_list = []

    for word in sentence.split():
        if word in directions:
            word_type = 'direction'
        elif word in verbs:
            word_type = 'verb'
        elif word in stop_words:
            word_type = 'stop'
        elif word in nouns:
            word_type = 'noun'
        else:
            number = convert_number(word)
            if number:
                word_type = 'number'
                word = number
            else:
                word_type = 'error'

        sentence_as_list.append((word_type, word))

    return sentence_as_list

def convert_number(s):
    try:
        return int(s)
    except ValueError:
        return None