#ifndef __MAIN_CHARACTER_HPP__
#define __MAIN_CHARACTER_HPP__

#include <irrlicht/irrlicht.h>
#include <irrklang/irrKlang.h>
#include "Player.h"
#include <vector>
#include <utility>
#include "Item.hpp"
#include "shader.h"


class ProgressCircle;

using namespace irrklang;

namespace irr
{
namespace scene
{
	class CFloorDecalSceneNode;
}
}

enum EMainCharacterActionState
{
	EMCAS_IDLE = 0,
	EMCAS_MOVE = 1,
	EMCAS_ROTATE = 2,
	EMCAS_JUMP = 4,
	EMCAS_ATTACK = 8,
	EMCAS_DEFEND = 16,
	EMCAS_RUNNING = 32,
	EMCAS_DEAD = 1 << 31
};

class MainCharacter: public Player
{
public:
	// constructor
	MainCharacter( GameWorld& gameWorld, irr::video::IVideoDriver& driver );

	// we need to recreated collisionresponse animator when switching players, otherwise the player teleporting doesn't work correctly
	virtual void RecreateCollisionResponseAnimator();

	// called every frame to update player
	virtual void Tick(irr::f32 delta);
	
	// returns the graph node of the actor by const reference
	virtual irr::scene::ISceneNode& GetNode() const { return *node; }
	
	// interface for identifying the type of actor
	virtual EActorType GetActorType() const { return ACTOR_PLAYER; }

	// get the user input for the player
	void DoInput();

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
	void setMoving( bool moving );
	void setRunning( bool running );
	bool isIdle() const;
	bool isDefending() const;
	bool isAttacking() const;
	bool isMoving() const;
	bool isRunning() const;


	void InitShader(irr::core::vector3df* lightPosition);

	// sets the player into firing state
	//void DoLaunchProjectile();
	
	
	// damage done to player
	virtual void ReceiveDamage( irr::f32 value );
	
	// check if the player is dead
	bool IsDead() const { return action == EMCAS_DEAD; }	

	// unbuffered mouse input 
	virtual void OnMouseEvent( const irr::SEvent::SMouseInput& mouseEvent ) {}
	
	/********************
	 Player Attribute GET FUNCTIONS
	 *******************/
	irr::s32 GetLevel() const {return _level;};
	irr::s32 GetAttackPoint() const {return _attack;};
	irr::s32 GetDefencePoint() const {return _defence;};
	irr::s32 GetMagicAttackPoint() const {return _magicattack;};
	irr::s32 GetMagicDefencePoint() const {return _magicdefence;};
	irr::s32 GetMagicLevel() const {return _magiclevel;}; 
	bool GetCharging() const {return _charging;};		//to get whether the player is charging for Magic
	//(std::vector< std::pair<Item*, int> >) GetItemBox() {return _itemBox;};
	irr::core::array< std::pair<Item*,int> >& GetItemBox() {return _itemBox;};
	irr::s32 GetEXP() const {return _exp;};
	
	/********************
	 Player Attribute SET FUNCTIONS
	 *******************/
	void SetLevel(irr::s32 level) {_level = level;};
	void SetAttackPoint(irr::s32 attack) { _attack = attack;};
	void SetDefencePoint(irr::s32 defence) { _defence = defence;};
	void SetMagicAttackPoint(irr::s32 magicattack) { _magicattack = magicattack;};
	void SetMagicDefencePoint(irr::s32 magicdefence) { _magicdefence = magicdefence;};
	void SetMagicLevel(irr::s32 magiclevel) { _magiclevel = magiclevel;}; 
	void SetCharging(bool charging) { _charging = charging;};		//to get whether the player is charging for Magic
	//void SetItemBox(std::vector< std::pair<Item*, int> > itemBox) { _itemBox = itemBox;};
	void SetItemBox(irr::core::array< std::pair<Item*, int> > itemBox) {_itemBox = itemBox;};
	void SetEXP(irr::s32 exp) {_exp = exp;};
	
protected:
	// destructor, protected to force user to call Actor::DestroyActor
	virtual ~MainCharacter();

private:
	// diallow copy constructor from being invoked
	MainCharacter( const MainCharacter& other );

	// updates the power of the throw meter
	void UpdateThrowMeter( irr::f32 delta );

	// updated the player position based on the value of translation set
	void UpdatePosition( irr::f32 delta ); 

	// MAYBE USEFUL!
	// drops a player footprint on the ground
	//! void PlaceRightFootPrint();
	//! void PlaceLeftFootPrint();

	// updates the move state based on the current value of player translation
	void SetMoveState( );

	// updates the move and arms state inside the tick function
	void UpdateRotationState( );
	void UpdateMoveState( irr::f32 delta );

	// scene graph node for player
	irr::scene::IAnimatedMeshSceneNode* node;

	// cached collision response animator
	irr::scene::ISceneNodeAnimatorCollisionResponse* collisionAnimator;
	
	// scene graph node for player's arms
	// irr::scene::IAnimatedMeshSceneNode* arms;
	
	// player's shadow, a simple static texture
	irr::scene::CFloorDecalSceneNode* shadowNode;

	EMainCharacterActionState action;

	// the meter which tracks how long the player is holding the throw button;
	irr::f32 throwFillupTimer;
	
	// whether the throw power should be increased
	bool bDoFillup;

	// player footstep sound effect
	ISound* sfxFootstep;
	irr::f32 sfxTimer;

	Shader* test1;
	/*********************
	 Player Attributes
	 **********************/
	
	irr::s32 _level;
	irr::s32 _attack;
	irr::s32 _defence;
	irr::s32 _magicattack;
	irr::s32 _magicdefence;
	irr::s32 _magiclevel;
	bool _charging;
	irr::core::array< std::pair<Item*,int> > _itemBox;
	irr::s32 _exp;
	
	
	/************
	 ************/

	GameWorld& world;

	class MyMainCharacterShaderCallBack : public irr::video::IShaderConstantSetCallBack
	{
		public:
			MyMainCharacterShaderCallBack(irr::IrrlichtDevice* device, irr::core::vector3df* lightPos) : _device(device), _lightPos(lightPos)
			{
			}

			virtual void OnSetConstants(irr::video::IMaterialRendererServices* services, irr::s32 userData)
			{
				irr::core::vector3df camPos = _device->getSceneManager()->getActiveCamera()->getAbsolutePosition();
				services->setVertexShaderConstant("view_position", reinterpret_cast<irr::f32*>(&camPos), 3);
				services->setVertexShaderConstant("LightPosition", reinterpret_cast<irr::f32*>(_lightPos), 3);
			}
		private:
			irr::IrrlichtDevice* _device;
			irr::core::vector3df* _lightPos;
	};

	class AttackAnimationEndCallBack : public irr::scene::IAnimationEndCallBack
	{
	public:
		explicit AttackAnimationEndCallBack( MainCharacter& m ) :
		theMainCharacter(m)
		{
		}

		virtual void OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode* theNode);
	private:
		MainCharacter& theMainCharacter;
	};

	AttackAnimationEndCallBack* attackCallBack;
};

#endif //__MAIN_CHARACTER_HPP__