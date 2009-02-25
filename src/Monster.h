/*
 *  FiniteStateMachine.h
 *  FYP
 *
 *  Created by Mr.JJ on 09年1月13日.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include <boost/mpl/list.hpp>
#include <boost/statechart/event.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/in_state_reaction.hpp>
#include <iostream>
#include <time.h>
#include <irrlicht/irrlicht.h>
#include <boost/timer.hpp>
#include "Player.hpp"

namespace sc = boost::statechart;
namespace mpl = boost::mpl;


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
	virtual void reaction(irr::scene::IAnimatedMeshSceneNode*,Player* ) const = 0;
	virtual void IdleTooLong(irr::scene::IAnimatedMeshSceneNode*,Player*,irr::core::vector3df) const = 0;
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
	void reaction(irr::scene::IAnimatedMeshSceneNode* _mon, Player* _player ){
		state_cast< const Name_test & >().reaction(_mon,_player);
	}
	void IdleTooLong(irr::scene::IAnimatedMeshSceneNode* _mon,Player* _player,irr::core::vector3df pos){
		state_cast< const Name_test & >().IdleTooLong(_mon,_player, pos);
	}
	
};

struct Death :Name_test,sc::simple_state< Death, FiniteStateMachine>{
	Death(){ std::cout<<"Death\n";};
	//virtual const std::string name () const { return "Death"; };
	virtual std::string GetName() const
    {
      return "Death";
    }
	virtual void test(int a,int s,int q) const
    {
      std::cout<<-a+s+q<<"\n";
    }
	virtual void reaction(irr::scene::IAnimatedMeshSceneNode* _mon,Player* _player) const{
		_mon->setLoopMode(true);
	}
	virtual void IdleTooLong(irr::scene::IAnimatedMeshSceneNode* _mon,Player* _player,irr::core::vector3df pos) const{
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
	virtual void reaction(irr::scene::IAnimatedMeshSceneNode* _mon, Player* _player) const{
	
	}
	virtual void IdleTooLong(irr::scene::IAnimatedMeshSceneNode* _mon,Player* _player, irr::core::vector3df pos) const{
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
		int i;
		for(i=0; i<100; i++)
			std::cout<<i<<"\n";
	};
	virtual std::string GetName() const
    {
      return "Attacking";
    }
	virtual void test(int a,int s,int q) const
    {
      std::cout<<a-s+q<<"\n";
    }
	virtual void reaction(irr::scene::IAnimatedMeshSceneNode* _mon, Player* _player) const{
		_player->reduceHealth(10);
	}
	virtual void IdleTooLong(irr::scene::IAnimatedMeshSceneNode* _mon,Player* _player, irr::core::vector3df pos) const{
	}
	virtual ~Attacking() {};
	//virtual const std::string name () const { return "Attacking"; };
	typedef sc::transition< EvPlayerWithinRange, Idle >reactions;
};

struct Idle :Name_test,  sc::simple_state< Idle, NotDeath> {
	Idle(){ std::cout<<"Idle\n"; /*std::cout<<GetName(1);*/ };
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
	virtual void reaction(irr::scene::IAnimatedMeshSceneNode* _mon, Player* _player) const{
		_mon->setLoopMode(false);
	}
	virtual void IdleTooLong(irr::scene::IAnimatedMeshSceneNode* _mon,Player* _player, irr::core::vector3df pos) const{
		std::cout<<"Move\n";
		_mon->setLoopMode(true);
		irr::core::matrix4 m;
		irr::core::vector3df targetPos = _player->getPosition();
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
		Tracing(){ std::cout<<"Tracing\n";};
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
		virtual void reaction(irr::scene::IAnimatedMeshSceneNode* _mon, Player* _player) const{
			//_mon->setLoopMode(true);
			irr::core::matrix4 m;
			irr::core::vector3df targetPos = _player->getPosition();
			m.setRotationDegrees(_mon->getRotation());
			m.transformVect(targetPos);
			float y = _mon->getPosition().Y;
			targetPos = _mon->getPosition()+((_player->getPosition() - _mon->getPosition())/42.5f); 
			targetPos.Y = y;
			
			irr::core::vector3df direction = _mon->getPosition()-targetPos;
			_mon->setRotation(direction.getHorizontalAngle());
			//std::cout<<targetPos<<"\n";
			_mon->setPosition(targetPos);
			_mon->updateAbsolutePosition();
			
		}
		virtual void IdleTooLong(irr::scene::IAnimatedMeshSceneNode* _mon,Player* _player, irr::core::vector3df pos) const{
		}
		typedef mpl::list< 
			sc::transition< EvPlayerWithinRange, Idle >,
			sc::transition< EvFiniteStateMachineOutOfRange, Idle >, 
			sc::transition< EvWithinAttackRange, Attacking > >reactions;
	
};
class Monster{
	public:
	
		Monster(irr::scene::IAnimatedMeshSceneNode*, irr::core::vector3df , irr::core::vector3df , float);
		~Monster(){};
		void change(char, Player*);
		void update(Player*);
		void Hit(int);
		int GetHealth();
			
	private:
		FiniteStateMachine FSM;
		irr::scene::IAnimatedMeshSceneNode *_monster;
		float _speed; 
		int Health;
		boost::timer* mon_timer;
		double timeout;
		bool moved;
		irr::core::vector3df target;
		irr::core::vector3df original;
		irr::core::vector3df pos;
	
};

