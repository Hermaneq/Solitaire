#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cstdlib>
#include <time.h>


using namespace std;


class Card
{
private:
    char sign;
    char color;
    int value;
    bool is_visible;
    bool is_red;
public:
    Card(char sign, char color, int value, bool is_red)
    {
        this->sign = sign;
        this->color = color;
        this->value = value;
        this->is_visible = true;
        this->is_red = is_red;
    }
    char getSign()
    {
        return this->sign;
    }
    char getColor
    ()
    {
        return this->color;
    }
    int getValue()
    {
        return this->value;
    }
    bool getVisible()
    {
        return this->is_visible;
    }
    void setVisible(bool x)
    {
        this->is_visible = x;
    }
    bool getRed()
    {
        return this->is_red;
    }
};

void shuffle_cards(vector<Card>& Deck, queue<Card>& Undealt_Cards, vector<vector<Card>>& Boards)
{
    srand(time(NULL));
    for (int i = 0; i < 24; i++)
    {
        int number = rand() % Deck.size();
        Undealt_Cards.push(Deck[number]);
        Deck.erase(Deck.begin() + number);
    }
    for (int i = 0; i < 7; i++)
    {
        for (int g = 0; g < i + 1; g++)
        {
            int number = rand() % Deck.size();
            Boards[i].push_back(Deck[number]);
            if (i != 0 and g != i) Boards[i][g].setVisible(false);
            Deck.erase(Deck.begin() + number);
        }
    }
}
void initialize(vector<Card>& Deck)
{
    char color = 'h';
    bool is_red = true;
    for (int i = 0; i < 4; i++)
    {
        if (i == 1)
        {
            color = 's';
            is_red = false;
        }
        else if (i == 2)
        {
            color = 'd';
            is_red = true;
        }
        else if (i == 3)
        {
            color = 'c';
            is_red = false;
        }

        Deck.push_back(Card('A', color, 1, is_red));
        Deck.push_back(Card('2', color, 2, is_red));
        Deck.push_back(Card('3', color, 3, is_red));
        Deck.push_back(Card('4', color, 4, is_red));
        Deck.push_back(Card('5', color, 5, is_red));
        Deck.push_back(Card('6', color, 6, is_red));
        Deck.push_back(Card('7', color, 7, is_red));
        Deck.push_back(Card('8', color, 8, is_red));
        Deck.push_back(Card('9', color, 9, is_red));
        Deck.push_back(Card('T', color, 10, is_red));
        Deck.push_back(Card('J', color, 11, is_red));
        Deck.push_back(Card('Q', color, 12, is_red));
        Deck.push_back(Card('K', color, 13, is_red));

    }
}

int find_max(vector<vector<Card> >& Boards)
{
    int max = 0;
    for (int i = 0; i < 7; i++)
    {
        if (Boards[i].size() > max) max = Boards[i].size();
    }
    return max;
}

bool check_win(vector<stack<Card>> Stacks)
{
    if (Stacks[0].size() == 13 and Stacks[1].size() == 13 and Stacks[2].size() == 13 and Stacks[3].size() == 13) return true;
    else return false;
}

void spread_queue(queue<Card>& Undealt_Cards, vector<Card>& Visible_cards)
{
    if (Undealt_Cards.size() > 0)
    {
        if (Visible_cards.size() == 0)
        {
            Visible_cards.push_back(Undealt_Cards.front());
            Undealt_Cards.pop();
        }
        else if (Visible_cards.size() < 3)
        {
            Visible_cards.push_back(Undealt_Cards.front());
            Undealt_Cards.pop();
        }
        else
        {
            Undealt_Cards.push(Visible_cards[0]);
            Visible_cards.erase(Visible_cards.begin());
            Visible_cards.push_back(Undealt_Cards.front());
            Undealt_Cards.pop();
        }
    }
    else if (Visible_cards.size() > 0)
    {
        Visible_cards.push_back(Visible_cards[0]);
        Visible_cards.erase(Visible_cards.begin());
        Visible_cards.push_back(Visible_cards[0]);
        Visible_cards.erase(Visible_cards.begin());
        Visible_cards.push_back(Visible_cards[0]);
        Visible_cards.erase(Visible_cards.begin());
    }
    else cout << "No cards left!" << endl;

}

void queue_board(vector<vector<Card>>& Boards, queue<Card>& Queue, vector<Card>& Visible_cards, int number)
{
    if (Visible_cards.size() > 0)
    {
        Card card = Visible_cards.back();
        if ((card.getSign() == 'K' and Boards[number - 1].size() == 0) or (Boards[number - 1].size() > 0 and card.getValue() == Boards[number - 1][Boards[number - 1].size() - 1].getValue() - 1 and card.getRed() != Boards[number - 1][Boards[number - 1].size() - 1].getRed()))
        {
            Visible_cards.pop_back();
            Boards[number - 1].push_back(card);
        }
        else
        {
            cout << "This move is not allowed!" << endl;
        }
    }
    else cout << "This move is not allowed" << endl;

}

void Queue_stack(vector<Card>& Visible_cards, int number, vector<stack<Card>>& Stacks, queue<Card>& Undealt_Cards)
{
    if (Visible_cards.size() > 0)
    {
        Card card = Visible_cards.back();
        if ((card.getSign() == 'A' and Stacks[number - 8].size() == 0) or (Stacks[number - 8].size() > 0 and card.getValue() == Stacks[number - 8].top().getValue() + 1 and card.getColor
        () == Stacks[number - 8].top().getColor
        ()))
        {
            Visible_cards.pop_back();
            Stacks[number - 8].push(card);
        }
        else
        {
            cout << "This move is not allowed!" << endl;
        }
    }
    else cout << "This move is not allowed" << endl;
}

void Stack_board(vector<stack<Card>>& Stacks, int stack_number, int board_number, vector<vector<Card>>& Boards)
{
    if (Stacks[stack_number - 8].size() > 0)
    {
        Card card = Stacks[stack_number - 8].top();
        if ((card.getSign() == 'K' and Boards[board_number - 1].size() == 0) or (card.getValue() == Boards[board_number - 1][Boards[board_number - 1].size() - 1].getValue() - 1 and card.getRed() != Boards[board_number - 1][Boards[board_number - 1].size() - 1].getRed()))
        {
            Stacks[stack_number - 8].pop();
            Boards[board_number - 1].push_back(card);
        }
        else cout << "Nie mozna wykonac takiego ruchu" << endl;

    }
    else cout << "Nie mozna wykonac takiego ruchu" << endl;
}

void board_stack(vector<vector<Card>>& Boards, int board_number, int stack_number, vector<stack<Card>>& Stacks)
{
    if (Boards[board_number - 1].size() > 0)
    {
        Card card = Boards[board_number - 1].back();
        if ((card.getSign() == 'A' and Stacks[stack_number - 8].size() == 0) or (Stacks[stack_number - 8].size() > 0 and Stacks[stack_number - 8].size() > 0 and card.getValue() == Stacks[stack_number - 8].top().getValue() + 1 and card.getColor
        () == Stacks[stack_number - 8].top().getColor
        ()))
        {
            Stacks[stack_number - 8].push(card);
            Boards[board_number - 1].pop_back();
            if (Boards[board_number - 1].size() > 0 and Boards[board_number - 1].back().getVisible() == false) Boards[board_number - 1].back().setVisible(true);
        }
        else cout << "This move is not allowed!" << endl;
    }
    else cout << "This move is not allowed!" << endl;
}

void board_board(vector<vector<Card>>& Boards, int board_number_1, int board_number_2, char sign, char color)
{
    if (Boards[board_number_1 - 1].size() > 0)
    {
        bool flaga = false;
        int pozycja;
        if (Boards[board_number_1 - 1].size() > 0)
        {
            for (int i = 0; i < Boards[board_number_1 - 1].size(); i++)
            {
                if (Boards[board_number_1 - 1][i].getSign() == sign && Boards[board_number_1 - 1][i].getColor
                () == color and Boards[board_number_1 - 1][i].getVisible() == true)
                {
                    flaga = true;
                    pozycja = i;
                }
            }
            if (flaga)
            {
                Card card = Boards[board_number_1 - 1][pozycja];
                int rozmiar = Boards[board_number_1 - 1].size() - 1;
                if (flaga and ((card.getSign() == 'K' and Boards[board_number_2 - 1].size() == 0) or (card.getValue() == Boards[board_number_2 - 1][Boards[board_number_2 - 1].size() - 1].getValue() - 1 and card.getRed() != Boards[board_number_2 - 1][Boards[board_number_2 - 1].size() - 1].getRed()) and (Boards[board_number_2 - 1].size() != 0)))
                {
                    for (int i = pozycja; i <= rozmiar; i++)
                    {
                        Boards[board_number_2 - 1].push_back(Boards[board_number_1 - 1][pozycja]);
                        Boards[board_number_1 - 1].erase(Boards[board_number_1 - 1].begin() + pozycja);
                    }

                    if (Boards[board_number_1 - 1].size() > 0 and Boards[board_number_1 - 1].back().getVisible() == false)
                    {
                        Boards[board_number_1 - 1].back().setVisible(true);
                    }
                }
                else
                {
                    cout << "This move is not allowed!" << endl;
                }
            }
            else
            {
                cout << "This move is not allowed" << endl;
            }
        }
        else
        {
            cout << "This move is not allowed" << endl;
        }
    }
    else
    {
        cout << "This move is not allowed" << endl;
    }

}


void print_info(vector<vector<Card>>& Boards, vector<stack<Card>>& Stacks, vector<Card>& Visible_cards)
{
    cout << "      0                             8   9   10  11   " << endl;
    for (int i = 0; i < 50; i++) cout << "-";
    cout << endl;
    if (Visible_cards.size() != 0)
    {
        cout << "    ";
        for (int i = 0; i < Visible_cards.size(); i++)
        {
            cout << Visible_cards[i].getSign() << Visible_cards[i].getColor
            () << " ";
        }
    }

    cout << "                        ";
    for (int i = 0; i < 4; i++)
    {
        if (Stacks[i].size() == 0)
        {
            cout << "0   ";
        }
        else
        {
            cout << Stacks[i].top().getSign() << Stacks[i].top().getColor
            () << "   ";
        }
    }
    cout << endl;
    for (int i = 0; i < 50; i++) cout << "-";
    cout << endl;
    int length = find_max(Boards);
    for (int i = 0; i < length; i++)
    {
        cout << "|";
        for (int g = 0; g < 7; g++)
        {
            if (Boards[g].size() > i)
            {
                if (Boards[g][i].getVisible() == true)
                {
                    cout << "  " << Boards[g][i].getSign() << Boards[g][i].getColor
                    () << "  ";
                }
                else
                {
                    cout << " ===  ";
                }
            }
            else
            {
                cout << "      ";
            }

            cout << "|";
        }
        cout << endl;
    }
    cout << "    1      2      3      4      5      6     7" << endl;


}


int main()
{
    vector<Card> Deck;
    initialize(Deck);
    vector<vector<Card>> Boards(7);
    vector<stack<Card>> Stacks(4);
    queue<Card> Undealt_Cards;
    vector<Card> Visible_cards;
    shuffle_cards(Deck, Undealt_Cards, Boards);
    print_info(Boards, Stacks, Visible_cards);
    bool flag = true;
    while (flag)
    {
        cout << "Enter your move: ";
        int move;
        cin >> move;

        if (move == 0)
        {
            string sign;
            cin >> sign;
            if (sign == "r") spread_queue(Undealt_Cards, Visible_cards);
            else
            {
                int number;
                cin >> number;
                if (number >= 1 and number <= 7)
                {
                    queue_board(Boards, Undealt_Cards, Visible_cards, number);
                }
                else if (number >= 8 and number <= 11)
                {
                    Queue_stack(Visible_cards, number, Stacks, Undealt_Cards);
                }
                else
                {
                    cout << "Nie ma takiego numeru" << endl;
                }

            }

        }
        else if (move >= 1 and move <= 7)
        {
            char sign;
            char color;
            int number;
            cin >> sign >> color;
            cin >> number;
            if (number >= 8 and number <= 11)
            {
                board_stack(Boards, move, number, Stacks);
            }
            else if (number >= 1 and number <= 7)
            {
                board_board(Boards, move, number, sign, color);
            }
            else
            {
                cout << "This number does not exist" << endl;
            }
        }
        else if (move >= 8 and move <= 11)
        {
            char sign;
            char color;
            int number;
            cin >> sign >> color;
            cin >> number;
            if (number >= 1 and number <= 7)
            {
                Stack_board(Stacks, move, number, Boards);
            }
            else cout << "This move does not exists" << endl;

        }
        else
        {
            cout << "This number does not exists" << endl;
        }

        print_info(Boards, Stacks, Visible_cards);

        flag = not check_win(Stacks);
    }
    cout << "Win" << endl;


    return 0;
}
