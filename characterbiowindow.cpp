#include "characterbiowindow.h"
#include "ui_characterbiowindow.h"

CharacterBioWindow::CharacterBioWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CharacterBioWindow)
{
    ui->setupUi(this);
}

CharacterBioWindow::~CharacterBioWindow()
{
    delete ui;
}

void CharacterBioWindow::on_returnToMenuButton_clicked()
{
    //switch view to gameMainMenu
    emit switchToWindow(0);
}

//Donald Trump
void CharacterBioWindow::on_character1Button_clicked()
{
    QString name("Donald John Trump, Sr");
    QString age("69, born June 14, 1946");
    QString from("Queens, New York");
    QString party("Republican");
    QString job("Business Leader, Reality Television Star");
    QString biography("Donald Trump became involved in profitable "
                "architectural projects in Manhattan when he was "
                "just 25 years old. At age 31 he opened the Grand "
                "Hyatt, making Trump the city's most controversial "
                "and well-known developer. At 58 years old Trump began "
                "starring in hit reality series \"The Apprentice\".");
    BioDialog bio;
    //update bio info for character
    bio.setModal(true);
    bio.updateInfo(name, age, from, party, job, biography);
    bio.exec();
}

//Hillary Clinton
void CharacterBioWindow::on_character2Button_clicked()
{
    QString name("Hillary Rodham Clinton");
    QString age("68, born October 26, 1947");
    QString from("Chicago, Illinois");
    QString party("Democrat");
    QString job("Government Official, Former First Lady");
    QString biography("Hillary Clinton earned a law degree from"
                      " Yale University, where she also met and married"
                      " Bill Clinton at the age of 28. After dabbling in"
                      " small political jobs, Hillary joined the presidential"
                      " imopeachment inquiry staff, and advised the House of "
                      " Representatives during the Watergate Scandal."                      " Later Hillary served as"
                      " first lady, and then was re-elected as a Senator. Making"
                      " her the first American first lady to win an elected"
                      " seat. Later she was appointed secretary of state by"
                      " President Barack Obama.");
    BioDialog bio;
    //update bio info for character
    bio.setModal(true);
    bio.updateInfo(name, age, from, party, job, biography);
    bio.exec();
}

//Bernie Sanders
void CharacterBioWindow::on_character3Button_clicked()
{
    QString name("Bernard Sanders");
    QString age("74, born Spetember 8, 1941");
    QString from("Brooklyn, New York");
    QString party("Democrat");
    QString job("Mayor, U.S. Senator, U.S. Representative");
    QString biography("Bernie Sanders attended the University "
                      "of Chicago, and became highly involved in "
                      "the civil rights movement. Bernie joined the "
                      "March on Washington in 1963 with Martin Luther "
                      "King jr. Sanders graduated with a political "
                      "science degree and took odd jobs until he became "
                      "a mayor in Vermont for nearly a decade. Afterwards "
                      "Bernie joined national politics in the House of "
                      "Representatives, then in 2007 he became a Senator.");
    BioDialog bio;
    //update bio info for character
    bio.setModal(true);
    bio.updateInfo(name, age, from, party, job, biography);
    bio.exec();
}

//Ted Cruz
void CharacterBioWindow::on_character4Button_clicked()
{
    QString name("Rafael Edward Cruz");
    QString age("45, born December 22, 1970");
    QString from("Calgary, Canada");
    QString party("Republican");
    QString job("Lawyer, U.S. Senator");
    QString biography("Ted Cruz grew up in Houston, Texas, later"
                      " attending Princeton, and then Harvard Law. "
                      " Gifted with public speaking, Cruz became "
                      " an award-winning debater at Princeton. "
                      " Cruz worked as an attorney  until he served"
                      " as an adviser on George W Bush's presidential"
                      " campaign in 2000. In 2012 Cruz won a seat as a"
                      " a U.S. Senator, where he helped organize the"
                      " governmental shutdown to protest Obamacare.");
    BioDialog bio;
    //update bio info for character
    bio.setModal(true);
    bio.updateInfo(name, age, from, party, job, biography);
    bio.exec();
}

//John Kasich
void CharacterBioWindow::on_character5Button_clicked()
{
    QString name("John Richard Kasich, Jr");
    QString age("63, born May 13, 1952");
    QString from("McKees Rocks, Pennsylvania");
    QString party("Republican");
    QString job("U.S. Governor");
    QString biography("John Kasich was raised a devout Catholic"
                      " who pursued community service through both"
                      " the church and his high school. After seriously "
                      " considering joining the priesthood, Kasich eventually"
                      " decided to attend college and studied political science."
                      " Kasich was invited to the White House by Richard"
                      " Nixon after writing to then president about his views."
                      " Kasich was elected to the Ohio State Senate in 1978,"
                      " and then elected to the House of Representatives in 1962.");
    BioDialog bio;
    //update bio info for character
    bio.setModal(true);
    bio.updateInfo(name, age, from, party, job, biography);
    bio.exec();
}
