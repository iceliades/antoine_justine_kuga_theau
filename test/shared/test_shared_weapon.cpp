// Justine Charlet 18/11/2020

//les includes
#include <boost/test/unit_test.hpp>
#include <string>
#include "../../src/shared/weapon.h"




namespace weapon{

        BOOST_AUTO_TEST_CASE(TestStaticAssert)
        {
            BOOST_CHECK(1);
        }

        BOOST_AUTO_TEST_CASE(TestWeapon)
        {   

            {
                // Weapon SWORD
                Weapon Sword("SWORD");

                BOOST_CHECK_EQUAL(Sword.getDammages(), 13);
                BOOST_CHECK_EQUAL(Sword.getMinRange(), 1);
                BOOST_CHECK_EQUAL(Sword.getMaxRange(), 2);
                


                Sword.setDammages(10);
                BOOST_CHECK_EQUAL(Sword.getDammages(),10) ;

                Sword.setMinRange(3);
                BOOST_CHECK_EQUAL(Sword.getMinRange(),3) ;

                Sword.setDodge(5);
                BOOST_CHECK_EQUAL(Sword.getMaxRange(),5);    


		
		// Weapon AXE
		Weapon Axe("AXE");

                BOOST_CHECK_EQUAL(Axe.getDammages(), 14);
                BOOST_CHECK_EQUAL(Axe.getMinRange(), 1);
                BOOST_CHECK_EQUAL(Axe.getMaxRange(), 1.5);
                


                Axe.setDammages(15);
                BOOST_CHECK_EQUAL(Axe.getDammages(),15) ;

                Axe.setMinRange(3);
                BOOST_CHECK_EQUAL(Sword.getMinRange(),3) ;

                Axe.setDodge(3.5);
                BOOST_CHECK_EQUAL(Axe.getMaxRange(),3.5);  





		// Weapon AXE
		Weapon Axe("AXE");

                BOOST_CHECK_EQUAL(Axe.getDammages(), 14);
                BOOST_CHECK_EQUAL(Axe.getMinRange(), 1);
                BOOST_CHECK_EQUAL(Axe.getMaxRange(), 1.5);
                


                Axe.setDammages(15);
                BOOST_CHECK_EQUAL(Axe.getDammages(),15) ;

                Axe.setMinRange(3);
                BOOST_CHECK_EQUAL(Axe.getMinRange(),3) ;

                Axe.setDodge(3.5);
                BOOST_CHECK_EQUAL(Axe.getMaxRange(),3.5); 






		// Weapon Spear
		Weapon Spear("SPEAR");

                BOOST_CHECK_EQUAL(Spear.getDammages(), 12);
                BOOST_CHECK_EQUAL(Spear.getMinRange(), 1);
                BOOST_CHECK_EQUAL(Spear.getMaxRange(), 2.5);
                


                Spear.setDammages(15);
                BOOST_CHECK_EQUAL(Spear.getDammages(),15) ;

                Spear.setMinRange(3);
                BOOST_CHECK_EQUAL(Spear.getMinRange(),3) ;

                Spear.setDodge(3.5);
                BOOST_CHECK_EQUAL(Spear.getMaxRange(),3.5); 






		// Weapon BOW
		Weapon Bow("BOW");

                BOOST_CHECK_EQUAL(Bow.getDammages(), 6);
                BOOST_CHECK_EQUAL(Bow.getMinRange(), 2);
                BOOST_CHECK_EQUAL(Bow.getMaxRange(), 8);
                


                Bow.setDammages(10);
                BOOST_CHECK_EQUAL(Bow.getDammages(),10) ;

                Bow.setMinRange(3);
                BOOST_CHECK_EQUAL(Bow.getMinRange(),3) ;

                Bow.setDodge(5);
                BOOST_CHECK_EQUAL(Bow.getMaxRange(),3.5); 





		// Weapon CROSSBOW
		Weapon Crossbow("CROSSBOW");

                BOOST_CHECK_EQUAL(Crossbow.getDammages(), 7);
                BOOST_CHECK_EQUAL(Crossbow.getMinRange(), 2);
                BOOST_CHECK_EQUAL(Crossbow.getMaxRange(), 7);
                


                Crossbow.setDammages(10);
                BOOST_CHECK_EQUAL(Crossbow.getDammages(),10) ;

                Crossbow.setMinRange(3);
                BOOST_CHECK_EQUAL(Crossbow.getMinRange(),3) ;

                Crossbow.setDodge(5);
                BOOST_CHECK_EQUAL(Crossbow.getMaxRange(),5); 





		// Weapon SLING
		Weapon Sling("SLING");

                BOOST_CHECK_EQUAL(Sling.getDammages(), 8);
                BOOST_CHECK_EQUAL(Sling.getMinRange(), 2);
                BOOST_CHECK_EQUAL(Sling.getMaxRange(), 6.5);
                


                Sling.setDammages(10);
                BOOST_CHECK_EQUAL(Sling.getDammages(),10) ;

                Sling.setMinRange(3);
                BOOST_CHECK_EQUAL(Sling.getMinRange(),3) ;

                Sling.setDodge(5);
                BOOST_CHECK_EQUAL(Sling.getMaxRange(),5); 


		// Weapon WAND
		Weapon Wand("WAND");

                BOOST_CHECK_EQUAL(Wand.getDammages(), 10);
                BOOST_CHECK_EQUAL(Wand.getMinRange(), 3);
                BOOST_CHECK_EQUAL(Wand.getMaxRange(), 4.5);
                


                Wand.setDammages(15);
                BOOST_CHECK_EQUAL(Wand.getDammages(),1) ;

                Wand.setMinRange(5);
                BOOST_CHECK_EQUAL(Wand.getMinRange(),5) ;

                Wand.setDodge(7);
                BOOST_CHECK_EQUAL(Wand.getMaxRange(),7); 



		// Weapon STICK
		Weapon Stick("STICK");

                BOOST_CHECK_EQUAL(Stick.getDammages(), 11);
                BOOST_CHECK_EQUAL(Stick.getMinRange(), 3);
                BOOST_CHECK_EQUAL(Stick.getMaxRange(), 4);
                


                Stick.setDammages(10);
                BOOST_CHECK_EQUAL(Stick.getDammages(),10) ;

                Stick.setMinRange(2);
                BOOST_CHECK_EQUAL(Stick.getMinRange(),2) ;

                Stick.setDodge(5);
                BOOST_CHECK_EQUAL(Stick.getMaxRange(),5); 



		// Weapon STRAP
		Weapon Strap("STRAP");

                BOOST_CHECK_EQUAL(Strap.getDammages(), 9);
                BOOST_CHECK_EQUAL(Strap.getMinRange(), 3);
                BOOST_CHECK_EQUAL(Strap.getMaxRange(), 5);
                


                Strap.setDammages(10);
                BOOST_CHECK_EQUAL(Strap.getDammages(),10) ;

                Strap.setMinRange(6);
                BOOST_CHECK_EQUAL(Strap.getMinRange(),6) ;

                Strap.setDodge(8);
                BOOST_CHECK_EQUAL(Strap.getMaxRange(),8); 





            }

       




        }
}
