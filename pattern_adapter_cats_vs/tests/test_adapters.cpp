#include <gtest/gtest.h>
#include <sstream>

#include "tiger.h"
#include "polar_bear.h"
#include "home_cat_adapter.h"
#include "polar_bear_adapter.h"

// ---------------------------------------------------------------------------
// Tiger (iWildCat) tests
// ---------------------------------------------------------------------------

TEST(Tiger, Breed_ReturnsTigerVulgarius)
{
    // Given:
    Tiger tiger;

    // When:
    std::string breed = tiger.Breed();

    // Then:
    EXPECT_EQ(breed, "Tiger vulgarius");
}

TEST(Tiger, Growl_PrintsToStdout)
{
    // Given:
    Tiger tiger;
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

    // When:
    tiger.Growl();
    std::cout.rdbuf(oldCout);

    // Then:
    EXPECT_FALSE(oss.str().empty());
}

TEST(Tiger, Scratch_PrintsToStdout)
{
    // Given:
    Tiger tiger;
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

    // When:
    tiger.Scratch();
    std::cout.rdbuf(oldCout);

    // Then:
    EXPECT_FALSE(oss.str().empty());
}

// ---------------------------------------------------------------------------
// HomeCatAdapter tests
// ---------------------------------------------------------------------------

TEST(HomeCatAdapter, Name_ReturnsTigerBreed)
{
    // Given:
    Tiger tiger;
    HomeCatAdapter adapter(tiger);

    // When:
    std::string name = adapter.Name();

    // Then:
    EXPECT_EQ(name, "Tiger vulgarius");
}

TEST(HomeCatAdapter, Meow_DelegatesToGrowl)
{
    // Given:
    Tiger tiger;
    HomeCatAdapter adapter(tiger);
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

    // When:
    adapter.Meow();
    std::cout.rdbuf(oldCout);

    // Then:
    EXPECT_FALSE(oss.str().empty());
}

TEST(HomeCatAdapter, SetName_OverridesBaseName)
{
    // Given:
    Tiger tiger;
    HomeCatAdapter adapter(tiger);

    // When:
    adapter.setName("Whiskers");

    // Then:
    // Name() returns Breed() from wild cat, not iHomeCat::_name — verify adapter behaviour
    EXPECT_EQ(adapter.Name(), "Tiger vulgarius");
}

// ---------------------------------------------------------------------------
// Usage example
// ---------------------------------------------------------------------------

TEST(HomeCatAdapter, UsageExample)
{
    // Demonstrate idiomatic adapter usage: wrap a Tiger in a HomeCatAdapter
    // and call it through the iHomeCat interface.
    Tiger tiger;
    iHomeCat& cat = *new HomeCatAdapter(tiger);

    EXPECT_FALSE(cat.Name().empty());

    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
    cat.Meow();
    cat.Scratch();
    std::cout.rdbuf(oldCout);

    EXPECT_FALSE(oss.str().empty());
    delete &cat;
}

// ---------------------------------------------------------------------------
// PolarBear tests
// ---------------------------------------------------------------------------

TEST(PolarBear, Species_ReturnsUrsusMaritimus)
{
    // Given:
    PolarBear polarBear;

    // When:
    std::string species = polarBear.Species();

    // Then:
    EXPECT_EQ(species, "Ursus maritimus arcticus");
}

TEST(PolarBear, Roar_PrintsToStdout)
{
    // Given:
    PolarBear polarBear;
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

    // When:
    polarBear.Roar();
    std::cout.rdbuf(oldCout);

    // Then:
    EXPECT_FALSE(oss.str().empty());
    EXPECT_NE(oss.str().find("Deep Arctic roar!"), std::string::npos);
}

TEST(PolarBear, Claw_PrintsToStdout)
{
    // Given:
    PolarBear polarBear;
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

    // When:
    polarBear.Claw();
    std::cout.rdbuf(oldCout);

    // Then:
    EXPECT_FALSE(oss.str().empty());
    EXPECT_NE(oss.str().find("Massive arctic claw swipe!"), std::string::npos);
}

TEST(PolarBear, HasNightVision_ReturnsTrue)
{
    // Given:
    PolarBear polarBear;

    // When:
    bool result = polarBear.hasNightVision();

    // Then:
    EXPECT_TRUE(result);
}

// ---------------------------------------------------------------------------
// PolarBearAdapter tests
// ---------------------------------------------------------------------------

TEST(PolarBearAdapter, Name_ReturnsPolarBearSpecies)
{
    // Given:
    PolarBear polarBear;
    PolarBearAdapter adapter(polarBear);

    // When:
    std::string name = adapter.Name();

    // Then:
    EXPECT_EQ(name, "Ursus maritimus arcticus");
}

TEST(PolarBearAdapter, Meow_DelegatesToRoar)
{
    // Given:
    PolarBear polarBear;
    PolarBearAdapter adapter(polarBear);
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

    // When:
    adapter.Meow();
    std::cout.rdbuf(oldCout);

    // Then:
    EXPECT_FALSE(oss.str().empty());
    EXPECT_NE(oss.str().find("Deep Arctic roar!"), std::string::npos);
}

TEST(PolarBearAdapter, Scratch_DelegatesToClaw)
{
    // Given:
    PolarBear polarBear;
    PolarBearAdapter adapter(polarBear);
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

    // When:
    adapter.Scratch();
    std::cout.rdbuf(oldCout);

    // Then:
    EXPECT_FALSE(oss.str().empty());
    EXPECT_NE(oss.str().find("Massive arctic claw swipe!"), std::string::npos);
}

TEST(PolarBearAdapter, UsageExample)
{
    // Given: A polar bear adapted to the iHomeCat interface
    PolarBear polarBear;
    iHomeCat& cat = *new PolarBearAdapter(polarBear);

    // When:
    std::string name = cat.Name();
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
    cat.Meow();
    cat.Scratch();
    std::cout.rdbuf(oldCout);

    // Then:
    EXPECT_EQ(name, "Ursus maritimus arcticus");
    EXPECT_NE(oss.str().find("Deep Arctic roar!"), std::string::npos);
    EXPECT_NE(oss.str().find("Massive arctic claw swipe!"), std::string::npos);
    delete &cat;
}
