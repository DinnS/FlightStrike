#pragma once
class AttributeComponent
{
private:
	
public:
	/*                VARIABLES            */
	// Leveling
	int level;
	int exp;
	int expNext;
	int attributePoints;

	// Stats
	int health;
	int heatlhMax;
	int damage;
	int armor;

	/*       CONSTRUCTORS/DESTRUCTORS      */

	AttributeComponent(int level);
	virtual ~AttributeComponent();

	/*				FUNCTION               */

	std::string debugPrint() const;

	void gainExp(const int exp);

	void resetHealth(const bool reset);

	// Update
	void updateLevel();
	

	void update();






};

