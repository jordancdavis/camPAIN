#ifndef MYCANVAS_H
#define MYCANVAS_H
#include "qsfmlcanvas.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
class MyCanvas : public QSFMLCanvas
{
public :
    MyCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size);
    void OnInit();
    void OnUpdate();
    void setCandidates(int user, int opponent);
    void setStageNum(int num);
    void updateOpponentSpriteImage(int round);
    void bernieRoundImage(int);
    void trumpRoundImage(int);
    void hilaryRoundImage(int);
    void johnRoundImage(int);
    void tedRoundImage(int);
    b2Body* CreateGround(b2World& World, float X, float Y);
    b2Body* CreateMyBox(b2World& World, int MouseX, int MouseY); // Spawns a box at MouseX, MouseY
    b2Body* CreateOppBox(b2World& World, int MouseX, int MouseY); // Spawns a box at MouseX, MouseY
    b2Body* CreateDropBox(b2World& World, int MouseX, int MouseY); // Spawns a box at MouseX, MouseY
    b2Body* CreateWall(b2World& World, float X, float Y);
    float timeStep;
    void Fight();
    float torque;
    float _gravity;
    float _myBounce;
    float _oppBounce;
    int itemCount = 0;


private :
    int oppNumber;
    QString bernie;
    QString donald;
    QString hilary;
    QString john;
    QString ted;
    QString money;
    QString teacup;
    QString texas;
    QString email;
    QString jew;
    QString candidateString;
    QString opponentString;
    QString background;
    QString itemString;
    sf::Clock myClock;
    sf::Texture CandidateImage;
    sf::Texture OpponentImage;
    sf::Texture BackgroundImage;
    sf::Sprite CandidateSprite;
    sf::Sprite OpponentSprite;
    sf::Sprite GroundSprite;
    sf::Sprite WallSprite;
    sf::Sprite BackgroundSprite;
    sf::Sprite ItemSprite;
    sf::Texture ItemImage;
    const float SCALE = 30.f;
    sf::Mouse mouse;
    b2Body* myBody;
    b2Body* oppBody;
    b2Body* groundBody;
    b2Body* leftWallBody;
    b2Body* rightWallBody;
    b2Body* topBody;
    b2Body* itemBody;

};
#endif // MYCANVAS_H
