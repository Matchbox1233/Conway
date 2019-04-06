#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>
using namespace sf;
using std::vector;
using std::cout;
using std::endl;


class Grid
{
public:
    Grid(unsigned int x = 1000, unsigned int y = 1000, unsigned int diffs = 50) : w(x),h(y),diff(diffs)
    {
        
    }

    void draw(RenderWindow & window)
    {
        for(int i=0;i<w;i+=diff)
        {   
            Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(i,0)),
                sf::Vertex(sf::Vector2f(i, h))
            };
            line[0].color = Color(0,0,0);
            line[1].color = Color(0,0,0);
            window.draw(line, 2, sf::Lines);
        }
        for(int i=0;i<h;i+=diff)
        {   
            Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(0,i)),
                sf::Vertex(sf::Vector2f(w,i))
            };
            line[0].color = Color(0,0,0);
            line[1].color = Color(0,0,0);

            window.draw(line, 2, sf::Lines);
        }
    }

    unsigned int w;
    unsigned int h;
    unsigned int diff;
};

class Square
{
public:
    Square()
    {

    }
    Square(int x_pos, int y_pos, float w, bool alive = false)
    {
        square = new RectangleShape(Vector2f(w,w));
        square->setPosition(Vector2f(x_pos,y_pos));
        aliveState = alive;
    }
    /*Square (const Square& other )
    {
        if(this != &other)
        {
            delete this->square;
            this->square = other.square;
        }
    }
    Square& operator=(const Square& other)
    {
        if(this != &other)
        {
            delete this->square;
            this->square = other.square;
        }
        return *this;
    }*/
    ~Square()
    {
        delete square;
    }

    void update()
    {
        if(aliveState)
        {
            square->setFillColor(Color::Black);
        }
        else
        {
            square->setFillColor(Color::White);
        }
        
    }

    void setFill(Color c = Color::White)
    {
        square->setFillColor(c);
    }

    void draw(RenderWindow &window)
    {
        window.draw(*square);
    }
    RectangleShape* square;

    bool aliveState;
private:
    
};

vector<vector<Square*>> update(vector<vector<Square*>> v)
{
    vector<vector<Square*>> tmp ;//= v;

    for(int i=0;i<v.size();i++)
    {
        tmp.push_back(vector<Square*>());
        for(int j=0;j<v[0].size();j++)
        {
            tmp[i].push_back(new Square(v[i][j]->square->getPosition().x,v[i][j]->square->getPosition().y,v[i][j]->square->getSize().x,v[i][j]->aliveState));
        }
    }

    for(int i=0;i<v.size();i++)
    {
        for(int j=0;j<v[0].size();j++)
        {
            int live_neighbours = 0;
            live_neighbours +=  v[(i-1)%v.size()][(j-1)%v[0].size()]->aliveState;
            live_neighbours +=  v[(i-1)%v.size()][(j)%v[0].size()]->aliveState;
            live_neighbours +=  v[(i-1)%v.size()][(j+1)%v[0].size()]->aliveState;

            live_neighbours +=  v[(i)%v.size()][(j-1)%v[0].size()]->aliveState;
            live_neighbours +=  v[(i)%v.size()][(j+1)%v[0].size()]->aliveState;

            live_neighbours +=  v[(i+1)%v.size()][(j-1)%v[0].size()]->aliveState;
            live_neighbours +=  v[(i+1)%v.size()][(j)%v[0].size()]->aliveState;
            live_neighbours +=  v[(i+1)%v.size()][(j+1)%v[0].size()]->aliveState;
            //cout <<" X:"<<i << " y:"<< j << " Live neighbours:"<< live_neighbours<<endl;
            if(v[i][j]->aliveState)
            {
                if(live_neighbours < 2)
                {
                    tmp[i][j]->aliveState = false;
                }
                else if(live_neighbours > 3)
                {
                    tmp[i][j]->aliveState = false;
                }
            }
            else
            {
                if(live_neighbours == 3)
                {
                    tmp[i][j]->aliveState = true;
                }
            }
        }
    }

    return tmp;
}


/*void update(vector<vector<Square*>> &v)
{
    vector<vector<Square*>> tmp = v;
    
    for(int i=0;i<v.size();i++)
    {
        for(int j=0;j<v[0].size();j++)
        {
            int live_neighbours = 0;
            live_neighbours +=  v[(i-1)%v.size()][(j-1)%v[0].size()]->aliveState;
            live_neighbours +=  v[(i-1)%v.size()][(j)%v[0].size()]->aliveState;
            live_neighbours +=  v[(i-1)%v.size()][(j+1)%v[0].size()]->aliveState;
            live_neighbours +=  v[(i)%v.size()][(j-1)%v[0].size()]->aliveState;
            live_neighbours +=  v[(i)%v.size()][(j+1)%v[0].size()]->aliveState;
            live_neighbours +=  v[(i+1)%v.size()][(j-1)%v[0].size()]->aliveState;
            live_neighbours +=  v[(i+1)%v.size()][(j)%v[0].size()]->aliveState;
            live_neighbours +=  v[(i+1)%v.size()][(j+1)%v[0].size()]->aliveState;
                
            //cout <<" X:"<<i << " y:"<< j << " Live neighbours:"<< live_neighbours<<endl;
            if(v[i][j]->aliveState)
            {
                if(live_neighbours < 2)
                {
                    //dead.push_back(Vector2i(i,j));
                    tmp[i][j]->aliveState = false;
                }
                else if(live_neighbours > 3)
                {
                    tmp[i][j]->aliveState = false;
                }
            }
            else
            {
                if(live_neighbours == 3)
                {
                    //nextGen[i][j] = true;
                    tmp[i][j]->aliveState = true;
                }
                
                
            }
            
        }
    }
    
    v=tmp;
   
}*/

/*vector<vector<Square*>> update(vector<vector<Square*>> v)
{
    vector<vector<Square*>> tmp = v;
    int size1 = v.size(), size2 = v[0].size();
    for(int i=0;i<size1;i++)
    {
        for(int j=0;j<size2;j++)
        {
            int alive = 0;
            for(int k=-1;k<=1;k++)
            {
                for(int l = -1; l<=1;l++)
                {
                    if(!(l==0 && k ==0))
                    {
                        alive += v[(i+k)%size1][(j+l)%size2]->aliveState;
                    }
                }
            }
            if(v[i][j]->aliveState)
            {
                if(alive < 2)
                {
                    tmp[i][j]->aliveState = false;
                }
                else if(alive > 3)
                {
                    tmp[i][j]->aliveState = false;
                }
            }
            else
            {
                if(alive == 3)
                {
                    tmp[i][j]->aliveState = true;
                }
            }
        }
    }
}*/

void killall(vector<vector<Square*>> &v)
{
    for(int i=0;i<v.size();i++)
    {
        for(int j=0;j<v[0].size();j++)
        {
            v[i][j]->aliveState=false;
        }
    }
}

int main()
{
    RenderWindow window(VideoMode(1000,1000),"Game of Life");
    window.setFramerateLimit(10);
    window.setActive();
    
    Vector2u size = window.getSize();

    Grid g(size.x,size.y,1000/40);
    
    
    int h = g.h/g.diff+1;
    int w = g.w/g.diff+1;
    //Square squares[h][w];

    std::vector<std::vector<Square*>> squares;

    bool edit_mode = true;


    for(int i=0;i<h;i++)
    {
        squares.push_back(vector<Square*>());
        for(int j=0;j<w;j++)
        {
            squares[i].push_back(new Square(i*g.diff+1,j*g.diff+2,g.diff-3));
        }
    }
    //squares[4][5]->aliveState=true;


    while (window.isOpen())
    {
        window.clear(sf::Color::White);
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if(event.type == Event::MouseButtonPressed)
            {
                if(edit_mode && event.mouseButton.button == Mouse::Button::Left)
                {
                    /*cout<<event.mouseButton.x<<" "<<event.mouseButton.y<<endl;
                    cout<<event.mouseButton.x/g.diff<< " "<< event.mouseButton.y/g.diff<<endl;*/
                    squares[event.mouseButton.x/g.diff][event.mouseButton.y/g.diff]->aliveState= !squares[event.mouseButton.x/g.diff][event.mouseButton.y/g.diff]->aliveState;
                    cout<< "Changed state on entity at X:"<< event.mouseButton.x/g.diff << " Y:"<<event.mouseButton.y/g.diff << " to "<< (squares[event.mouseButton.x/g.diff][event.mouseButton.y/g.diff]->aliveState? "Alive" : "Dead")<<endl;
                }
            }
            else if(event.type == Event::KeyPressed)
            {
                if(event.key.code == Keyboard::Q)
                {
                    cout<<"Close request recieved. Application will exit."<<endl;
                    window.close();
                }
                if(edit_mode && event.key.code == Keyboard::C)
                {
                    cout<< "Killed all entities." <<endl;
                    killall(squares);
                }
                if(event.key.code == Keyboard::E)
                {
                    edit_mode = !edit_mode;
                    if(edit_mode)
                    {
                        cout<< "Changed to edit mode."<<endl;
                    }
                    else
                    {
                        cout<< "Changed to simulation mode."<<endl;
                    }
                    
                }
            }
            
                
        }

        /*s.draw(window);
        s.square->setPosition(Vector2f(s.square->getPosition().x+1,s.square->getPosition().y));*/
        g.draw(window);

        for(int i=0;i<h;i++)
        {
            for( int j=0; j<w;j++)
            {
                squares[i][j]->draw(window);
            }
        }

        window.display();
        if(!edit_mode) squares = update(squares);
        for(int i=0;i<h;i++)
        {
            for( int j=0; j<w;j++)
            {
                squares[i][j]->update();
            }
        }
    }
     
    return EXIT_SUCCESS;
}