import random
class Card(object):
    """Represents a standard playing card"""
    suit_names = ['Clubs', 'Diamonds', 'Hearts', 'Spades']
    rank_names = ['None', 'Ace','2','3','4','5','6','7','8','9','10','Jack','Queen','King']

    def __init__(self, suit = 0, rank = 2):
        self.suit = suit
        self.rank = rank

    def __str__(self):
        #return '%s of %s' % (rank_names[self.rank], suit_names[self.suit]) # error, self cannot dot suit_names and rank_names
        return '%s of %s' % (Card.rank_names[self.rank], Card.suit_names[self.suit])

    def __cmp__(self, other):
        t1 = self.suit, self.rank
        t2 = other.suit, other.rank
        return cmp(t1, t2)

class Deck(object):

    def __init__(self):
        self.cards = []
        for suit in range(4):
            for rank in range(1, 14):
                card = Card(suit, rank)
                self.cards.append(card)

    def __str__(self):
        res = []
        for card in self.cards:
            res.append( str(card) )
        return '\n'.join(res)

    def pop_card(self):
        return self.cards.pop() # remove the last card in the list

    def add_card(self, card):
        self.cards.append(card)

    def shuffle(self):
        random.shuffle(self.cards)
    
    def sort(self):
        pass

    def move_cards(self, hand, number):
        for i in range(number):
            hand.add_card( self.pop_card() )

class Hand(Deck):
    """Represents a hand of playing cards"""

    def __init__(self, label = ''):
        self.cards = []
        self.label = label



if __name__=='__main__':
    queen_of_diamonds = Card(1, 12)
    print queen_of_diamonds
    card1 = Card(2, 11)
    print card1

    deck = Deck()
    print deck
    card = deck.pop_card()
    hand = Hand('New hand')
    print hand.label
    print hand.cards
    hand.add_card( card )
    print hand


