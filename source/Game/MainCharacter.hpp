#ifndef __MAIN_CHARACTER_HPP__
#define __MAIN_CHARACTER_HPP__

#include <irrlicht/irrlicht.h>
#include <irrklang/irrKlang.h>

#include <vector>
#include <utility>

#include "Item.hpp"
#include "MDiscItem.hpp"
#include "Player.hpp"
#include "shader.hpp"
#include "WeaponItem.hpp"

class Monster;

enum EMainCharacterActionState
{
	EMCAS_IDLE = 0,
	EMCAS_MOVE = 1,
	EMCAS_ROTATE = 2,
	EMCAS_JUMP = 4,
	EMCAS_ATTACK = 8,
	EMCAS_MAGICATTACK = 16,
	EMCAS_DEFEND = 32,
	EMCAS_RUNNING = 64,
	EMCAS_DIEING = 128, // XD
	EMCAS_DEAD = 1 << 31
};

class MainCharacter: public Player
{
public:
	typedef irr::core::array< std::pair<Item*, int> > ItemCollection;

	// constructor
	MainCharacter( GameEngine&, GameWorld& );

	// we need to recreated collisionresponse animator when switching players, otherwise the player teleporting doesn't work correctly
	virtual void RecreateCollisionResponseAnimator();

	// called every frame to update player
	virtual void Tick(irr::f32 delta);
	
	// returns the graph node of the actor by const reference
	virtual irr::scene::ISceneNode& GetNode() const { return *node; }
	virtual irr::core::vector3df GetRadius() {
		irr::core::vector3df temp = node->getBoundingBox().MaxEdge - node->getBoundingBox().getCenter();
		return irr::core::vector3df(temp.X, 0, temp.Z);
	}
	
	// interface for identifying the type of actor
	virtual EActorType GetActorType() const { return ACTOR_PLAYER; }

	// get the user input for the player
	void DoInput(irr::f32 delta);

	// set the movement translation vector for player
	virtual void SetTranslation( const irr::core::vector3df& trans );
	
	// set the movement rotation vector for player
	virtual void SetRotation( const irr::core::vector3df& rot );

	// accessor methods for node position and rotation
	virtual irr::core::vector3df GetNodePosition() const { node->updateAbsolutePosition(); return node->getAbsolutePosition(); }
	virtual irr::core::vector3df GetNodeRotation() const { return node->getRotation(); }
	virtual void SetNodePosition( const irr::core::vector3df& vect ) { node->setPosition(vect); node->updateAbsolutePosition(); }
	virtual void SetNodeRotation( const irr::core::vector3df& vect ) { node->setRotation(vect); }
	void setIdle();
	void setDefending( bool defending );
	void setAttacking( bool attacking );
	void setCasting( bool casting );
	void setMoving( bool moving, bool backward = false );
	void setRunning( bool running );
	bool isIdle() const;
	bool isDefending() const;
	bool isAttacking() const;
	bool isCasting() const;
	bool isMoving() const;
	bool isRunning() const;
	bool isDieing() const;

	irr::core::vector3df getTargetPos();

	void InitShader(irr::core::vector3df* lightPosition);
	
	// damage done to player
	virtual void ReceiveDamage( irr::f32 value );
	
	// check if the player is dead
	bool IsDead() const { return action == EMCAS_DEAD; }	

	// unbuffered mouse input 
	virtual void OnMouseEvent( const irr::SEvent::SMouseInput& mouseEvent ) {}
	
	/********************
	 Player Attribute GET FUNCTIONS
	 *******************/
	irr::s32 GetLevel() const {return _level;}
	irr::s32 GetAttackPoint() const {return _attack;}
	irr::s32 GetDefencePoint() const {return _defence;}
	irr::s32 GetMagicAttackPoint() const {return _magicattack;}
	irr::s32 GetMagicDefencePoint() const {return _magicdefence;}
	irr::s32 GetMagicLevel() const {return _magiclevel;}
	irr::u32 GetChargingProgress() const {return _magicChargeProgress;}
	bool GetCharging() const {return _charging;} //to get whether the player is charging for Magic
	ItemCollection& GetItemBox() {return _itemBox;}
	irr::u32 GetEXP() const {return _exp;}
	WeaponItem* GetCurrentWeapon() const {return _currentWeapon;};
	MDiscItem* GetCurrentMagic() const {return _currentMagic;};
	irr::scene::ISceneNode* getWeaponNode() { return weaponNode; }
	Monster* GetTarget() { return monsterTarget; }
	void SetTarget( Monster* newTarget );
	irr::u32 GetMoney() {return _money;};
	
	bool GetCombo() const {return _combo;};
	irr::s32 GetComboNum() const {return _comboNum;};
	
	/********************
	 Player Attribute SET FUNCTIONS
	 *******************/
	void SetLevel(irr::s32 level) {_level = level;}
	void SetAttackPoint(irr::s32 attack) { _attack = attack;}
	void SetDefencePoint(irr::s32 defence) { _defence = defence;}
	void SetMagicAttackPoint(irr::s32 magicattack) { _magicattack = magicattack;}
	void SetMagicDefencePoint(irr::s32 magicdefence) { _magicdefence = magicdefence;}
	void SetMagicLevel(irr::s32 magiclevel) { _magiclevel = magiclevel;}
	void SetCharging(bool charging) { _charging = charging;} //to get whether the player is charging for Magic
	void SetChargingProgress(irr::u32 magicChargeProgress) {_magicChargeProgress = magicChargeProgress;}
	void SetItemBox(ItemCollection itemBox) {_itemBox = itemBox;};
	void SetEXP(irr::u32 exp);
	void SetCurrentWeapon(WeaponItem* currentWeapon);
	void SetCurrentMagic(MDiscItem* currentMagic) ;
	void SetCombo(bool combo) {_combo = combo;};
	void SetComboNum(irr::s32 comboNum) {_comboNum = comboNum;};
	void SetMoney(irr::u32 money) {_money = money;};

protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~MainCharacter();

private:
	// diallow copy constructor from being invoked
	MainCharacter( const MainCharacter& other );

	void lockNextTarget();

	// scene graph node for player
	irr::scene::IAnimatedMeshSceneNode* node;
	irr::scene::ISceneNode* weaponNode;
	irr::scene::ISceneNode* ATFieldNode;
	irr::scene::ISceneNode* MagicNode;
	irr::scene::ISceneNode* targetIndicator;

	// cached collision response animator
	irr::scene::ISceneNodeAnimatorCollisionResponse* collisionAnimator;

	EMainCharacterActionState action;
	
	// whether the throw power should be increased
	bool bDoFillup;

	Shader* test1;
	/*********************
	 Player Attributes
	 **********************/
	irr::u32 _money;	
	irr::s32 _level;
	irr::s32 _attack;
	irr::s32 _defence;
	irr::s32 _magicattack;
	irr::s32 _magicdefence;
	irr::s32 _magiclevel;
	irr::u32 _magicChargeProgress;
	bool _charging;
	ItemCollection _itemBox;
	irr::u32 _exp;
	WeaponItem* _currentWeapon;
	MDiscItem* _currentMagic;
	bool _combo;
	irr::s32 _comboNum;
	Monster* monsterTarget;
	bool MagicFired;
	irr::f32 MagicBonusValue;

	boost::timer* magic_timer;
	irr::u32 magicFlyTime;

	boost::timer* combo_timer;
	
	irr::f32 timeElapsed;
	Shader* FireBall;
	Shader* Ice;
	Shader* Lightning;
	Shader* Cyclone;

	class AttackAnimationEndCallBack : public irr::scene::IAnimationEndCallBack
	{
	public:
		explicit AttackAnimationEndCallBack( GameWorld& gameWorld, MainCharacter& m ) :
		theMainCharacter(m),
		world(gameWorld)
		{
		}

		virtual void OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode* theNode);
	private:
		MainCharacter& theMainCharacter;
		GameWorld& world;
	}* attackCallBack;

	class DeathAnimationEndCallBack : public irr::scene::IAnimationEndCallBack
	{
	public:
		explicit DeathAnimationEndCallBack( GameWorld& gameWorld, MainCharacter& m ) :
		theMainCharacter(m),
		world(gameWorld)
		{
		}

		virtual void OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode* theNode);
	private:
		MainCharacter& theMainCharacter;
		GameWorld& world;
	}* endCallBack;

	friend class AttackAnimationEndCallBack;
	friend class DeathAnimationEndCallBack;
};

#endif //__MAIN_CHARACTER_HPP__
