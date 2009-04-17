/*
 *  FiniteStateMachine.h
 *  FYP
 *
 *  Created by Mr.JJ on 09?????3??
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __MONSTER_HPP__
#define __MONSTER_HPP__

#include <boost/mpl/list.hpp>
#include <boost/statechart/event.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/in_state_reaction.hpp>
#include <iostream>
#include <time.h>
#include "Actor.hpp"
#include <irrlicht/irrlicht.h>
#include <boost/timer.hpp>
#include "Player.hpp"
#include "ParticleManager.hpp"
#include <math.h>
#include "MainCharacter.hpp"


namespace sc = boost::statechart;
namespace mpl = boost::mpl;

struct FiniteStateMachine;

class Monster: public Actor{
public:
	typedef irr::core::array< std::pair<Item*, int> > ItemCollection;
	Monster( GameEngine&, GameWorld& gameWorld, irr::s32 exp, irr::s32 attk, irr::s32 def, irr::s32 mattk, irr::s32 mdef, ItemCollection monItemBox);
	~Monster(){
		delete FSM;
		//collisionAnimator->drop();
		//collisionAnimator = NULL;
		
	//	irr::scene::ISceneManager& smgr = world.GetSceneManager();
	//	smgr.addToDeletionQueue( _monster );
	};
	// we need to recreated collisionresponse animator when switching players, otherwise the player teleporting doesn't work correctly
	virtual void RecreateCollisionResponseAnimator();

	//void change(Player&);
	void update(Player&, irr::f32 delta);
	void Tick( irr::f32 delta );
	virtual irr::scene::ISceneNode& GetNode() const {return *_monster;}
	virtual irr::core::vector3df GetRadius() {
		irr::core::vector3df temp = _monster->getBoundingBox().MaxEdge - _monster->getBoundingBox().getCenter();
		return irr::core::vector3df(temp.X, 0, temp.Z);
	}
	EActorType GetActorType() const { return ACTOR_ENEMY; }
	bool ShouldPerformCollisionCheck() const { return false; }
	void ReceiveDamage(irr::f32 );
	void DestroyActor( Actor*& actorToDestroy );
	void SetNodePosition( const irr::core::vector3df& vect ) { _monster->setPosition(vect); _monster->updateAbsolutePosition(); }
	virtual void ReSetPosition(irr::core::vector3df);
	//int GetHealth();
	void CheckActorPosition(irr::core::vector3df&,Player&);
	irr::s32 GetEXP() {return _exp;};
	irr::s32 GetAttk() {return _attk;};
	irr::s32 GetDef() {return _def;};
	irr::s32 GetMAttk() {return _mattk;};
	irr::s32 GetMDef() {return _mdef;};

	irr::scene::IAnimatedMeshSceneNode& GetMeshNode(){ return *_monster;}
		
private:
	irr::s32 _exp;
	irr::s32 _attk;
	irr::s32 _def;
	irr::s32 _mattk;
	irr::s32 _mdef;
	FiniteStateMachine* FSM;
	irr::scene::IAnimatedMeshSceneNode *_monster;
	ItemCollection _monItemBox;

	// cached collision response animator
	irr::scene::ISceneNodeAnimatorCollisionResponse* collisionAnimator;

	float _speed; 
	irr::f32 health;
	boost::timer* mon_timer;
	boost::timer* attack_timer;
	boost::timer* death_timer;
	double timeout;
	bool moved;
	irr::core::vector3df target;
	irr::core::vector3df original;
	irr::core::vector3df pos;
	//int  Health;

	ParticleManager* sparking;
};

//EVENT-------------------------------------------------------------
struct EvIdleTooLong : sc::event< EvIdleTooLong > { virtual ~EvIdleTooLong () {};};
struct EvPlayerWithinRange : sc::event< EvPlayerWithinRange > { virtual ~EvPlayerWithinRange () {};};
struct EvPlayerOutOfRange : sc::event< EvPlayerOutOfRange > { virtual ~EvPlayerOutOfRange () {};};
struct EvFiniteStateMachineOutOfRange : sc::event< EvFiniteStateMachineOutOfRange > { virtual ~EvFiniteStateMachineOutOfRange () {};};
struct EvWithinAttackRange : sc::event < EvWithinAttackRange > { virtual ~EvWithinAttackRange () {};};
struct EvOutOfAttackRange : sc::event< EvOutOfAttackRange > { virtual ~EvOutOfAttackRange () {};};
struct EvDie : sc::event< EvDie > { virtual ~EvDie () {};};

//EVENT--------------------------------------------------------------


//STATES------------------------------------------------------------
//Base Class

struct Name_test
{
	virtual std::string GetName() const = 0;
	virtual void test(int, int, int) const =0;
	virtual void reaction(irr::scene::IAnimatedMeshSceneNode*,Player&,irr::core::vector3df, Monster*) const = 0;
	virtual void IdleTooLong(irr::scene::IAnimatedMeshSceneNode*,Player&,irr::core::vector3df) const = 0;
};

/*struct State
{
	virtual ~State () {};
	virtual const std::string name () const = 0;
};*/


struct NotDeath;
struct Idle;
struct Tracing;
struct Attacking;

struct Death;
struct NotDeath;


struct FiniteStateMachine : sc::state_machine<FiniteStateMachine, NotDeath >{
	FiniteStateMachine(){};
	virtual ~FiniteStateMachine () {};
/*	const State& state ()
		{
			return state_cast<const State&>();
		}
*/	std::string GetName() const
	{
		return state_cast< const Name_test & >().GetName();
	}
	void test(int a, int s, int q) const
	{
		state_cast<const Name_test & >().test(a,s,q);
	}
	void reaction(irr::scene::IAnimatedMeshSceneNode* _mon, Player& _player,irr::core::vector3df target, Monster* _monster){
		state_cast< const Name_test & >().reaction(_mon,_player, target, _monster);
	}
	void IdleTooLong(irr::scene::IAnimatedMeshSceneNode* _mon,Player& _player,irr::core::vector3df pos){
		state_cast< const Name_test & >().IdleTooLong(_mon,_player, pos);
	}
	
};

struct Death :Name_test,sc::simple_state< Death, FiniteStateMachine>{
	Death(){
		std::cout<<"Death\n";
	};
	//virtual const std::string name () const { return "Death"; };
	virtual std::string GetName() const
    {
      return "Death";
    }
	virtual void test(int a,int s,int q) const
    {
      std::cout<<-a+s+q<<"\n";
    }
	virtual void reaction(irr::scene::IAnimatedMeshSceneNode* _mon,Player& _player,irr::core::vector3df target, Monster* _monster  ) const{
		_mon->setLoopMode(true);
	}
	virtual void IdleTooLong(irr::scene::IAnimatedMeshSceneNode* _mon,Player& _player,irr::core::vector3df pos) const{
	}
	virtual ~Death() {};
};

struct NotDeath :Name_test, sc::simple_state<NotDeath, FiniteStateMachine, Idle >{
	NotDeath(){};
	virtual ~ NotDeath() {};
	virtual std::string GetName() const
    {
      return "Not Death";
    }
	virtual void test(int a,int s,int q) const
    {
      std::cout<<"a-s-q"<<"\n";
    }
	virtual void reaction(irr::scene::IAnimatedMeshSceneNode* _mon, Player& _player,irr::core::vector3df target, Monster* _monster  ) const{
	
	}
	virtual void IdleTooLong(irr::scene::IAnimatedMeshSceneNode* _mon,Player& _player, irr::core::vector3df pos) const{
	}
	// virtual const std::string name () const { return "NotDeath"; };
	typedef sc::transition< EvDie, Death>reactions ;
};

struct Idle;
struct Tracing;
struct Attacking;

struct Attacking :Name_test, sc::simple_state< Attacking, NotDeath>{
	Attacking(){ 
		std::cout<<"Attacking\n";
	};
	virtual std::string GetName() const
    {
      return "Attacking";
    }
	virtual void test(int a,int s,int q) const
    {
      std::cout<<a-s+q<<"\n";
    }
	
	virtual void reaction(irr::scene::IAnimatedMeshSceneNode* _mon, Player& _player, irr::core::vector3df target, class Monster* _monster ) const
	{
		//_player->reduceHealth(1);
		//physical damage to player
		//irr::s32 monAttk = _mon->GetAttk();
		irr::s32 monAttk = _monster->GetAttk();
		irr::s32 playerDef = ((MainCharacter&)_player).GetDefencePoint();
		std::cout << "Monster Attk = " << monAttk << std::endl;
		std::cout << "Player Defence = " << playerDef << std::endl;
		irr::s32 damage = 0;
		if (((MainCharacter&)_player).isDefending())
		{
			if (monAttk - playerDef*2/3 > 0)
			{
				damage = monAttk - (playerDef*2/3) * 2;
			}
		}
		else
		{
			if (monAttk - (playerDef*2/3)*2 >0 )
			{
				damage = monAttk - playerDef*2/3;
			}
		}
		irr::s32 offset = damage/5 * (rand()%601)/300;
		std::cout << "Damage = " << damage-offset << std::endl;
		_player.ReceiveDamage(damage-offset);
	}
	
	virtual void IdleTooLong(irr::scene::IAnimatedMeshSceneNode* _mon,Player& _player, irr::core::vector3df pos) const{
	}
	
	virtual ~Attacking() {};
	//virtual const std::string name () const { return "Attacking"; };
	
	typedef sc::transition< EvFiniteStateMachineOutOfRange, Idle >reactions;
};

struct Idle :Name_test,  sc::simple_state< Idle, NotDeath> {
	Idle(){
		//std::cout<<"Idle\n"; /*std::cout<<GetName(1);*/
	};
	virtual ~Idle() {};
	
	
	//virtual const std::string name () const { return "Idle"; };
	virtual std::string GetName() const
    {
		return "Idle";
    }
	virtual void test(int a,int s,int q) const
    {
      std::cout<<a+s-q<<"\n";
    }
	virtual void reaction(irr::scene::IAnimatedMeshSceneNode* _mon, Player& _player,irr::core::vector3df target, Monster* _monster  ) const{
		_mon->setLoopMode(false);
	}
	virtual void IdleTooLong(irr::scene::IAnimatedMeshSceneNode* _mon,Player& _player, irr::core::vector3df pos) const{
		//std::cout<<"Move\n";
		_mon->setLoopMode(true);
		irr::core::matrix4 m;
		irr::core::vector3df targetPos = _player.GetNodePosition();
		m.setRotationDegrees(_mon->getRotation());
		m.transformVect(targetPos);
		targetPos=pos;
		//std::cout<<targetPos<<"\n";
		
		irr::core::vector3df direction = _mon->getPosition()-targetPos;
		_mon->setRotation(direction.getHorizontalAngle());
		_mon->setPosition(_mon->getPosition()+(targetPos-_mon->getPosition())/5.0f);
		_mon->updateAbsolutePosition();
		_mon->setLoopMode(false);

	}
	typedef mpl::list< 
		sc::transition< EvIdleTooLong, Idle>,
		sc::transition< EvFiniteStateMachineOutOfRange, Idle >,
		sc::transition< EvPlayerWithinRange, Tracing>, 
		sc::transition< EvWithinAttackRange, Attacking > >reactions;
	
};
struct Tracing :Name_test, sc::simple_state< Tracing, NotDeath> {
		Tracing(){ 
			//std::cout<<"Tracing\n";
		};
		virtual ~Tracing() {};
	//	virtual const std::string name () const { return "Tracing"; };
		virtual std::string GetName() const
		{
			return "Tracing";
		}
		virtual void test(int a,int s,int q) const
		{
			std::cout<<a+s+q<<"\n";
		}
		virtual void reaction(irr::scene::IAnimatedMeshSceneNode* _mon, Player& _player,irr::core::vector3df target, Monster* _monster  ) const{
			//_mon->setLoopMode(true);
			irr::core::matrix4 m;
			irr::core::vector3df targetPos = _player.GetNodePosition();
			m.setRotationDegrees(_mon->getRotation());
			m.transformVect(targetPos);
			float y = _mon->getPosition().Y;
			//targetPos = _mon->getPosition()+((_player.GetNodePosition() - _mon->getPosition())/42.5f); 
			//targetPos.Y = y;
			targetPos = target;
			irr::core::vector3df direction = _mon->getPosition()-targetPos;
			_mon->setRotation(direction.getHorizontalAngle());
			//std::cout<<targetPos<<"\n";
			_mon->setPosition(targetPos);
			_mon->updateAbsolutePosition();
			
		}
		virtual void IdleTooLong(irr::scene::IAnimatedMeshSceneNode* _mon,Player& _player, irr::core::vector3df pos) const{
		}
		typedef mpl::list< 
			sc::transition< EvPlayerWithinRange, Tracing >,
			sc::transition< EvFiniteStateMachineOutOfRange, Idle >, 
			sc::transition< EvWithinAttackRange, Attacking > >reactions;
};

#endif //__MONSTER_HPP__
