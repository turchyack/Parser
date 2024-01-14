#include "pch.h"
#include "../Parser/Identifier.h"
#include <sstream>

TEST(Simple, Test1) {
	Identifier id;     // или auto id = Identifier();
	EXPECT_EQ(Identifier::Code::AN, id.value);

}
TEST(Simple1, ToStr) {
	Identifier id;
	EXPECT_EQ("AN", id.ToStr());
}
TEST(Valid, Test3) {
	{
		Identifier id;
		std::stringstream stream("AN213");

		id.ReadFromStream(stream);
		EXPECT_EQ(Identifier::Code::AN, id.value);
	}

	{
		Identifier id(Identifier::Code::CO);
		std::stringstream stream("AN");
		id.ReadFromStream(stream);
		EXPECT_EQ(Identifier::Code::AN, id.value);
	}

	{
		Identifier id;
		std::stringstream stream("CO");
		id.ReadFromStream(stream);
		EXPECT_EQ(Identifier::Code::CO, id.value);
	}
}

TEST(Error, Test1) {

	{
		Identifier id;
		std::stringstream stream("DU");
		EXPECT_ANY_THROW(id.ReadFromStream(stream));
	}

	{
		Identifier id;
		std::stringstream stream("");
		EXPECT_ANY_THROW(id.ReadFromStream(stream));
	}



}