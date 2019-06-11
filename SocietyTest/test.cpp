#include "pch.h"
#include "../SocietyLibrary/myMain.h"
#include "../SocietyLibrary/ColorManipulation.h"
#include <SFML/Graphics.hpp>

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
  EXPECT_EQ(myMain(), 5);
  for (int r = 0; r < 256; r++)
  {
	  for (int g = 0; g < 256; g++)
	  {
		  sf::Color color(r, g, 25);
		  sf::Color color2(r, g, 255);
		  sf::Color color3(r, g, 0);
		  sf::Color color4(r, 0, g);
		  sf::Color color5(r, 255, g);
		  sf::Color color6(r, 125, g);
		  sf::Color color7(0, g, r);
		  sf::Color color8(250, g, r);
		  sf::Color color9(255, g, r);
		  EXPECT_EQ(GetStringColor(GetColorString(color)), color);
		  EXPECT_EQ(GetStringColor(GetColorString(color2)), color2); 
		  EXPECT_EQ(GetStringColor(GetColorString(color3)), color3);
		  EXPECT_EQ(GetStringColor(GetColorString(color4)), color4);
		  EXPECT_EQ(GetStringColor(GetColorString(color5)), color5); 
		  EXPECT_EQ(GetStringColor(GetColorString(color6)), color6);
		  EXPECT_EQ(GetStringColor(GetColorString(color7)), color7);
		  EXPECT_EQ(GetStringColor(GetColorString(color8)), color8);
		  EXPECT_EQ(GetStringColor(GetColorString(color9)), color9);


		  /*for (int b = 0; b < 256; b++)
		  {
			  
		  }*/
	  }
  }

}