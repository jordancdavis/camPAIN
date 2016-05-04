#include "mycanvas.h"
#include <iostream>
#include <string>
#include <QDir>
#include <Box2D/Box2D.h>
#include <QDebug>

MyCanvas::MyCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size) : QSFMLCanvas(Parent, Position, Size)
{
    bernie = "/Users/Resources/BerniePainders/sprite_0.png";
    donald = "/Users/Resources/DonaldTrump/sprite_0.png";
    hilary = "/Users/Resources/Hillary/hillary0.png";
    john = "/Users/Resources/JohnKasich/sprite_0.png";
    ted = "/Users/Resources/TedCruz/sprite_0.png";
    money = "/Users/Resources/TrumpDromp.png";
    jew = "/Users/Resources/Dreidel.png";
    texas = "/Users/Resources/Texas.png";
    email = "/Users/Resources/email.png";
    teacup = "/Users/Resources/TeaCruz.png";
    background = "/Users/Resources/WhiteHouse.png";
    candidateString = "";
    opponentString = "";
    timeStep = 1/30.f;
    torque = 0.f;
    _myBounce = 0.5f;     //body slides across another body.
    _oppBounce = 0.5f;      //bounciness.. how responds when contacted

}

void MyCanvas::OnInit()
{
    // Load the image
    if (!CandidateImage.loadFromFile(candidateString.toStdString())) {
        std::cout << "Loading error"<< std::endl;
    }

    updateOpponentSpriteImage(0);
    if (!ItemImage.loadFromFile(itemString.toStdString())) {
        std::cout << "Loading error"<< std::endl;
    }

    // Setup the sprite
    CandidateSprite.setTexture(CandidateImage);
    CandidateSprite.scale(sf::Vector2f(5.f, 5.f));

    // Setup the sprite
    OpponentSprite.setTexture(OpponentImage);
    OpponentSprite.scale(sf::Vector2f(-5.f, 5.f));

//    GroundSprite.setTexture(GroundImage);
    GroundSprite.scale(sf::Vector2f(-1.f,1.f));

//    WallSprite.setTexture(WallImage);
    WallSprite.scale(sf::Vector2f(-1.f, 1.f));

    ItemSprite.setTexture(ItemImage);
    ItemSprite.scale(sf::Vector2f(1.0f, 1.0f));

    myClock.restart();
}
void MyCanvas::OnUpdate()
{

    RenderWindow::setFramerateLimit(60);
    timeStep = 1/30.f;

    /** Prepare the world */
    b2Vec2 Gravity(0.f, _gravity+10);
    b2World World(Gravity);
    sf::Vector2i pixelPos(0,0);
    sf::Vector2f worldPos = this->mapPixelToCoords(pixelPos);
    CreateGround(World, worldPos.x - 110, worldPos.y + 620);
    CreateWall(World, worldPos.x - 110, worldPos.y + 620);
    CreateWall(World, worldPos.x + 1800.f, worldPos.y + 620);
    CreateGround(World, worldPos.x - 110, worldPos.y - 110);
    CreateMyBox(World, worldPos.x, worldPos.y + 600);
    CreateOppBox(World, worldPos.x+1400, worldPos.y + 600);
    CreateDropBox(World, -10000, -1000);


    int loadCount = 0;
    while (loadCount <= 5)
        {
            /** Simulate the world */
            World.Step(timeStep + 0.f, 8,3);
            RenderWindow::clear(sf::Color(0, 0, 255));
                   for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
                   {

                       if (BodyIterator->GetPosition() == myBody->GetPosition())
                       {
                           CandidateSprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
                           CandidateSprite.setRotation(BodyIterator->GetAngle() * 180/b2_pi);
                           RenderWindow::draw(CandidateSprite);

                       } else if(BodyIterator->GetPosition() == oppBody->GetPosition())
                       {
                           OpponentSprite.setPosition((SCALE * BodyIterator->GetPosition().x) + 300, SCALE * BodyIterator->GetPosition().y);
                           OpponentSprite.setRotation(BodyIterator->GetAngle() * 180/b2_pi);
                           RenderWindow::draw(BackgroundSprite);
                           RenderWindow::draw(OpponentSprite);
                       }
                       else
                       {
                           sf::Sprite GroundSprite;
                           GroundSprite.setColor(sf::Color::Black);
                           GroundSprite.setOrigin(worldPos.x, worldPos.y);
                           GroundSprite.setPosition(BodyIterator->GetPosition().x * SCALE, BodyIterator->GetPosition().y * SCALE);
                           GroundSprite.setRotation(180/b2_pi * BodyIterator->GetAngle());
                           RenderWindow::draw(GroundSprite);
                       }
                   }
                   RenderWindow::display();
                   loadCount++;
           }
}


void MyCanvas::Fight(){
    RenderWindow::setFramerateLimit(60);
    timeStep = 1/30.f;

    /** Prepare the world */
    b2Vec2 Gravity(0.f, _gravity+10);
    b2World World(Gravity);
    sf::Vector2i pixelPos(0,0);
    sf::Vector2f worldPos = this->mapPixelToCoords(pixelPos);
    groundBody = CreateGround(World, worldPos.x - 110, worldPos.y + 620);
    leftWallBody = CreateWall(World, worldPos.x - 110, worldPos.y + 620);
    rightWallBody = CreateWall(World, worldPos.x + 1800.f, worldPos.y + 620);
    topBody = CreateGround(World, worldPos.x - 110, worldPos.y - 110);
    CreateMyBox(World, worldPos.x, worldPos.y + 600);
    CreateOppBox(World, worldPos.x+1400, worldPos.y + 600);

    int frameCount = 0;
    int itemWait = 0;
    while (RenderWindow::isOpen())
        {
            /** When the user clicks space add a box into the world */

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))){
                 myBody->SetLinearVelocity(b2Vec2(-20.f,-40.f));
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                myBody->SetLinearVelocity(b2Vec2(-20.f,9.8f));
            } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed((sf::Keyboard::Up))) {
                myBody->SetLinearVelocity(b2Vec2(20.f,-40.f));
            } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                myBody->SetLinearVelocity(b2Vec2(20.f,9.8f));
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                myBody->SetLinearVelocity(b2Vec2(0.f,-40.f));
            } else {
                myBody->SetLinearVelocity(b2Vec2(0.f,9.8f));
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && itemCount < 1 && itemWait < frameCount){
                itemWait+=frameCount+15;
                itemCount++;
                CreateDropBox(World,worldPos.x+1475, worldPos.y + 1);
            }


            if(timeStep == 0){
                itemCount = 0;
                break;
            }

            /** Simulate the world */

            World.Step(timeStep + 0.f, 8,3);
            RenderWindow::draw(BackgroundSprite);

                   for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
                   {

                       if (BodyIterator->GetPosition() == myBody->GetPosition())
                       {
                           CandidateSprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
                           CandidateSprite.setRotation(BodyIterator->GetAngle() * 180/b2_pi);
                           RenderWindow::draw(CandidateSprite);

                       }
                       else if(BodyIterator->GetPosition() == oppBody->GetPosition())
                       {
                           OpponentSprite.setPosition((SCALE * BodyIterator->GetPosition().x) + 300, SCALE * BodyIterator->GetPosition().y);
                           OpponentSprite.setRotation(BodyIterator->GetAngle() * 180/b2_pi);
                           RenderWindow::draw(OpponentSprite);
                       }
                       else if (BodyIterator->GetPosition() == groundBody->GetPosition())
                       {
                           sf::Sprite GroundSprite;

                           GroundSprite.setColor(sf::Color::Black);
                           GroundSprite.setOrigin(worldPos.x, worldPos.y);
                           GroundSprite.setPosition(BodyIterator->GetPosition().x * SCALE, BodyIterator->GetPosition().y * SCALE);
                           GroundSprite.setRotation(180/b2_pi * BodyIterator->GetAngle());
                           RenderWindow::draw(GroundSprite);
                       }
                       else if (BodyIterator->GetPosition() == leftWallBody->GetPosition())
                       {
                           sf::Sprite GroundSprite;

                           GroundSprite.setColor(sf::Color::Black);
                           GroundSprite.setOrigin(worldPos.x, worldPos.y);
                           GroundSprite.setPosition(BodyIterator->GetPosition().x * SCALE, BodyIterator->GetPosition().y * SCALE);
                           GroundSprite.setRotation(180/b2_pi * BodyIterator->GetAngle());
                           RenderWindow::draw(GroundSprite);
                       }
                       else if (BodyIterator->GetPosition() == rightWallBody->GetPosition())
                       {
                           sf::Sprite GroundSprite;

                           GroundSprite.setColor(sf::Color::Black);
                           GroundSprite.setOrigin(worldPos.x, worldPos.y);
                           GroundSprite.setPosition(BodyIterator->GetPosition().x * SCALE, BodyIterator->GetPosition().y * SCALE);
                           GroundSprite.setRotation(180/b2_pi * BodyIterator->GetAngle());
                           RenderWindow::draw(GroundSprite);
                       }
                       else if (BodyIterator->GetPosition() == topBody->GetPosition())
                       {
                           sf::Sprite GroundSprite;

                           GroundSprite.setColor(sf::Color::Black);
                           GroundSprite.setOrigin(worldPos.x, worldPos.y);
                           GroundSprite.setPosition(BodyIterator->GetPosition().x * SCALE, BodyIterator->GetPosition().y * SCALE);
                           GroundSprite.setRotation(180/b2_pi * BodyIterator->GetAngle());
                           RenderWindow::draw(GroundSprite);
                       }
                       else {
                           //change object
                           ItemSprite.setPosition((SCALE * BodyIterator->GetPosition().x) , SCALE * BodyIterator->GetPosition().y);
                           ItemSprite.setRotation(BodyIterator->GetAngle() * 180/b2_pi);
                           itemBody->ApplyLinearImpulse(b2Vec2(0,BodyIterator->GetMass()), BodyIterator->GetPosition(),true);
                           RenderWindow::draw(ItemSprite);

                       }


                   }
                   RenderWindow::display();

                   if(frameCount > 750){
                       timeStep = 0;
                       itemCount = 0;
                   }
                   frameCount++;
           }

}

void MyCanvas::setCandidates(int user, int opponent){
    oppNumber = opponent;
    if(user == 0){
        candidateString = bernie;
        itemString = jew;
    } else if (user == 1){
        candidateString = donald;
        itemString = money;
    } else if (user == 2) {
        candidateString = hilary;
        itemString = email;
    } else if (user == 3) {
        candidateString = john;
        itemString = texas;
    } else if (user == 4) {
        candidateString = ted;
        itemString = teacup;
    }
    updateOpponentSpriteImage(0);
}


b2Body* MyCanvas::CreateGround(b2World& World, float X, float Y)
{
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(X/30.f, Y/30.f);
    BodyDef.type = b2_staticBody;
    b2Body* Ground = World.CreateBody(&BodyDef);
    b2PolygonShape Shape;
    Shape.SetAsBox(1800, 1); // Creates a box shape. Divide your desired width and height by 2.
    b2FixtureDef FixtureDef;
    FixtureDef.density = 0.f;  // Sets the density of the body
    FixtureDef.shape = &Shape; // Sets the shape
    Ground->CreateFixture(&FixtureDef); // Apply the fixture definition
    return Ground;
}

b2Body* MyCanvas::CreateWall(b2World& World, float X, float Y)
{
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(X/30.f, Y/30.f);
    BodyDef.type = b2_staticBody;
    b2Body* Wall = World.CreateBody(&BodyDef);
    b2PolygonShape Shape;
    Shape.SetAsBox(3, 1000); // Creates a box shape. Divide your desired width and height by 2.
    b2FixtureDef FixtureDef;
    FixtureDef.density = 5.f;  // Sets the density of the body
    FixtureDef.shape = &Shape; // Sets the shape
    Wall->CreateFixture(&FixtureDef); // Apply the fixture definition
    return Wall;
}

b2Body* MyCanvas::CreateMyBox(b2World& World, int MouseX, int MouseY)
{
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(MouseX/SCALE, MouseY/SCALE);
    BodyDef.type = b2_dynamicBody;
    myBody = World.CreateBody(&BodyDef);
    b2PolygonShape Shape;
    Shape.SetAsBox((250.f/2)/SCALE, (250.f/2)/SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 0.f;
    FixtureDef.friction = 0.5f;
    FixtureDef.restitution = _myBounce;
    FixtureDef.shape = &Shape;
    myBody->CreateFixture(&FixtureDef);
}

b2Body* MyCanvas::CreateOppBox(b2World& World, int MouseX, int MouseY)
{
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(MouseX/SCALE, MouseY/SCALE);
    BodyDef.type = b2_dynamicBody;
    oppBody = World.CreateBody(&BodyDef);
    b2PolygonShape Shape;
    Shape.SetAsBox((250.f/2)/SCALE, (250.f/2)/SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 0.f;       //overall mas of your object.
    FixtureDef.friction = 0.5f;     //body slides across another body.
    FixtureDef.restitution = _oppBounce;      //bounciness.. how responds when contacted
    FixtureDef.shape = &Shape;
    oppBody->CreateFixture(&FixtureDef);
}



b2Body* MyCanvas::CreateDropBox(b2World& World, int MouseX, int MouseY)
{
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(MouseX/SCALE, MouseY/SCALE);
    BodyDef.type = b2_dynamicBody;
    itemBody = World.CreateBody(&BodyDef);
    b2PolygonShape Shape;
    Shape.SetAsBox(((250.f/2)/SCALE)/4, ((250.f/2)/SCALE)/4);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 0.0f;       //overall mas of your object.
    FixtureDef.friction = 0.5f;     //body slides across another body.
    FixtureDef.restitution = 0.5;      //bounciness.. how responds when contacted
    FixtureDef.shape = &Shape;
    itemBody->CreateFixture(&FixtureDef);
    itemBody->SetFixedRotation(true);
}


void MyCanvas::setStageNum(int stage){
   //get correct stage
   if(stage == 0){
       background = "/Users/Resources/IntroLevel.png";
   }
   if(stage == 1){
       background = "/Users/Resources/Crowd.png";
   }
   if(stage == 2){
       background = "/Users/Resources/SpotlightCam.png";
   }
   if(stage == 3){
       background = "/Users/Resources/Rocket.png";
   }
   if(stage == 4){
       background = "/Users/Resources/WhiteHouse.png";
   }
   if (!BackgroundImage.loadFromFile(background.toStdString())) {
       std::cout << "Loading error"<< std::endl;
   }
   BackgroundSprite.setTexture(BackgroundImage);
   BackgroundSprite.setPosition(0, 0);
   BackgroundSprite.scale(sf::Vector2f(6.5, 3.f));
}

void MyCanvas::updateOpponentSpriteImage(int round){

    if(oppNumber == 0){
        bernieRoundImage(round);
    } else if (oppNumber == 1){
        trumpRoundImage(round);
    } else if (oppNumber == 2){
        hilaryRoundImage(round);
    } else if (oppNumber == 3){
        johnRoundImage(round);
    } else if (oppNumber == 4){
        tedRoundImage(round);
    }

    if (!OpponentImage.loadFromFile(opponentString.toStdString())) {
        std::cout << "Loading error"<< std::endl;
    }
    // Setup the sprite
    OpponentSprite.setTexture(OpponentImage);

}

void MyCanvas::bernieRoundImage(int round){
    if(round == 0){
        opponentString = "/Users/Resources/BerniePainders/sprite_0.png";
    } else if (round == 1){
        opponentString = "/Users/Resources/BerniePainders/sprite_1.png";
    } else if (round == 2){
        opponentString = "/Users/Resources/BerniePainders/sprite_2.png";
    } else if (round == 3){
        opponentString = "/Users/Resources/BerniePainders/sprite_3.png";
    } else if (round == 4){
        opponentString = "/Users/Resources/BerniePainders/sprite_4.png";
    }
}

void MyCanvas::trumpRoundImage(int round){
    if(round == 0){
        opponentString = "/Users/Resources/DonaldTrump/sprite_0.png";
    } else if (round == 1){
        opponentString = "/Users/Resources/DonaldTrump/sprite_1.png";
    } else if (round == 2){
        opponentString = "/Users/Resources/DonaldTrump/sprite_2.png";
    } else if (round == 3){
        opponentString = "/Users/Resources/DonaldTrump/sprite_3.png";
    } else if (round == 4){
        opponentString = "/Users/Resources/DonaldTrump/sprite_4.png";
    }
}

void MyCanvas::hilaryRoundImage(int round){
    if(round == 0){
        opponentString = "/Users/Resources/Hillary/hillary0.png";
    } else if (round == 1){
        opponentString = "/Users/Resources/Hillary/hillary1.png";
    } else if (round == 2){
        opponentString = "/Users/Resources/Hillary/hillary2.png";
    } else if (round == 3){
        opponentString = "/Users/Resources/Hillary/hillary3.png";
    } else if (round == 4){
        opponentString = "/Users/Resources/Hillary/hillary4.png";
    }
}

void MyCanvas::johnRoundImage(int round){
    if(round == 0){
        opponentString = "/Users/Resources/JohnKasich/sprite_0.png";
    } else if (round == 1){
        opponentString = "/Users/Resources/JohnKasich/sprite_1.png";
    } else if (round == 2){
        opponentString = "/Users/Resources/JohnKasich/sprite_2.png";
    } else if (round == 3){
        opponentString = "/Users/Resources/JohnKasich/sprite_3.png";
    } else if (round == 4){
        opponentString = "/Users/Resources/JohnKasich/sprite_4.png";
    }
}

void MyCanvas::tedRoundImage(int round){
    if(round == 0){
        opponentString = "/Users/Resources/TedCruz/sprite_0.png";
    } else if (round == 1){
        opponentString = "/Users/Resources/TedCruz/sprite_1.png";
    } else if (round == 2){
        opponentString = "/Users/Resources/TedCruz/sprite_2.png";
    } else if (round == 3){
        opponentString = "/Users/Resources/TedCruz/sprite_3.png";
    } else if (round == 4){
        opponentString = "/Users/Resources/TedCruz/sprite_4.png";
    }
}
