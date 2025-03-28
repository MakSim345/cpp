#include "gen.h"


class Card
{
public:
    Card(Rank rankP, Suit suitP)
        :rankM(rankP)
        ,suitM(suitP)
        {}

    Rank getRank() const { return rankM; }
    Suit getSuit() const { return suitM; }
    // Function to convert Rank to string

    std::string getSuitStr(int suitP)
    {
    switch (suitP)
        {
        case HEARTS:   return "HEARTS";
        case DIAMONDS:   return "DIAMONDS";
        case CLUBS:   return "CLUBS";
        case SPADES:   return "SPADES";

        default:
            return "INVALID SUIT"; // Handle invalid input
        }
    }

    std::string getRankStr(int rankP)
    {
    switch (rankP)
        {
        case ACE:   return "ACE";
        case TWO:   return "TWO";
        case THREE: return "THREE";
        case FOUR:  return "FOUR";
        case FIVE:  return "FIVE";
        case SIX:   return "SIX";
        case SEVEN: return "SEVEN";
        case EIGHT: return "EIGHT";
        case NINE:  return "NINE";
        case TEN:   return "TEN";
        case JACK:  return "JACK";
        case QUEEN: return "QUEEN";
        case KING:  return "KING";
        default:
            return "INVALID RANK"; // Handle invalid input
        }

    }
    // Method to get a string representation of the card
    std::string toString() const
    {
        std::string rankNames[] = { "INVALID", "ACE", "TWO", "THREE", "FOUR", "FIVE",
                                     "SIX", "SEVEN", "EIGHT", "NINE", "TEN",
                                     "JACK", "QUEEN", "KING" };
        std::string suitNames[] = { "HEARTS", "DIAMONDS", "CLUBS", "SPADES" };

        return rankNames[rankM] + " of " + suitNames[suitM];
        // return getRankStr(rankM) + " of " + getSuitStr(suitM);
    }


private:
    Rank rankM;
    Suit suitM;
};


class Player
{
public:

    Player(const std::string& nameP)
        :m_Name(nameP) {}

    void Erase()
    // void Erase() override // override means it is originally virtual function and recreated here
    {
        std::cout << "Erased: " << m_Name << std::endl;
    }

    void addCard(std::unique_ptr<Card> pCardP)
    {
        hand_.push_back(std::move(pCardP));
    }

    std::string getName()  {return m_Name;}

    int getHandValue() const
    {
        int value = 0;
        int aces = 0;

        for (const auto& card : hand_)
        {
            int cardValue = card->getRank();
            if (cardValue >= 10)
            {
                cardValue = 10;
            }
            else if (cardValue == ACE)
            {
                aces++;
                cardValue = 11;
            }
            value += cardValue;
        }
        while (value > 21 && aces > 0)
        {
            value -= 10;
            aces--;
        }

        return value;
    }

private:
    std::string m_Name;
    vector <std::unique_ptr <Card> > hand_;
};


class Deck
{
public:
    Deck()
    {
        for (int suit = HEARTS; suit <= SPADES; suit++)
        {
            for (int rank = ACE; rank <= KING; rank++)
            {
                std::unique_ptr<Card> card = std::make_unique<Card>(static_cast<Rank>(rank), static_cast<Suit>(suit));
                // std::unique_ptr cannot be copied.
                cardsArray.push_back(std::move(card));
            }
        }
    };

     // Method to print all cards in the deck
    void printCards() const
    {
        for (const auto& card : cardsArray)
        {
            std::cout << card->toString() << std::endl;
        }
    }

    void shufleDeck()
    {
        random_device rd;
        mt19937 g(rd());
        std::shuffle(cardsArray.begin(), cardsArray.end(), g);
        printCards();
    }

    std::unique_ptr<Card> drawCard()
    {
        if(cardsArray.empty())
        {
            return nullptr;
        }

        std::unique_ptr<Card> card = std::move(cardsArray.back());
        cardsArray.pop_back();
        std::cout << "Draw Card:" << std::endl;
        //std::cout << card->getRank() << std::endl;
        //std::cout << card->getSuit() << std::endl;
        std::cout << card->toString() << std::endl;
        return card;
    }

private:
    vector <std::unique_ptr<Card>> cardsArray;
};


int main()
{
    // shuffle_cards();
    std::cout << " -----> App start\n";

    Deck deck;
    deck.shufleDeck();

    Player player("Player_01");
    Player dealer("Dealer");

    player.addCard(deck.drawCard());
    player.addCard(deck.drawCard());

    dealer.addCard(deck.drawCard());
    dealer.addCard(deck.drawCard());

    std::cout << "Player hand value:" << player.getHandValue()  << std::endl;
    std::cout << "Dealer hand value:" << dealer.getHandValue()  << std::endl;

    std::cout << " -----> App stop\n";

    return 0;
}

