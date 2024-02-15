#include "pch.h"
#include "../Parser/Identifier.h"
#include <sstream>




class IdentifierTest :public testing::Test {
public:
	IdentifierTest() : id2_(Identifier::Code::CO) {}

protected:
	Identifier id1_;
	Identifier id2_;
	Identifier id3_;
	Identifier* id4_;


	void SetUp() {
		id4_ = new Identifier(Identifier::Code::CO);

	}
	void TearDown() { delete id4_; }


};


TEST_F(IdentifierTest, CodeValue) {

	EXPECT_EQ(Identifier::Code::AN, id1_.value);
	EXPECT_EQ(Identifier::Code::CO, id2_.value);
	EXPECT_EQ(Identifier::Code::AN, id3_.value);
	EXPECT_EQ(Identifier::Code::AN, id3_.value);

}


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