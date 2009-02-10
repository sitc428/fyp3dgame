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
#include <irrlicht/irrlicht.h>

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
  virtual std::string GetName(int&) const = 0;
  virtual void test(int, int, int) const =0;
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
*/	std::string GetName(int& a) const
	{
		return state_cast< const Name_test & >().GetName(a);
	}
	void test(int a, int s, int q) const
	{
		state_cast<const Name_test & >().test(a,s,q);
	}
	
};

struct Death :Name_test,sc::simple_state< Death, FiniteStateMachine>{
	Death(){ std::cout<<"Death\n";};
	//virtual const std::string name () const { return "Death"; };
	virtual std::string GetName(int& a ) const
    {
      return "State : Death\n";
    }
	virtual void test(int a,int s,int q) const
    {
      std::cout<<-a+s+q<<"\n";
    }
	virtual ~Death() {};
};

struct NotDeath :Name_test, sc::simple_state<NotDeath, FiniteStateMachine, Idle >{
	NotDeath(){};
	virtual ~ NotDeath() {};
	virtual std::string GetName(int& a) const
    {
      return "State : Not Death\n";
    }
	virtual void test(int a,int s,int q) const
    {
      std::cout<<"a-s-q"<<"\n";
    }
	// virtual const std::string name () const { return "NotDeath"; };
	typedef sc::transition< EvDie, Death>reactions;
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
	virtual std::string GetName(int& a) const
    {
      return "State : Attacking\n";
    }
	virtual void test(int a,int s,int q) const
    {
      std::cout<<a-s+q<<"\n";
    }
	virtual ~Attacking() {};
	//virtual const std::string name () const { return "Attacking"; };
	typedef sc::transition< EvOutOfAttackRange, Idle >reactions;
};

struct Idle :Name_test,  sc::simple_state< Idle, NotDeath> {
	Idle(){ std::cout<<"Idle\n"; /*std::cout<<GetName(1);*/ };
	virtual ~Idle() {};
	
	
	//virtual const std::string name () const { return "Idle"; };
	virtual std::string GetName(int& a) const
    {
		a++;
		std::cout<<a<<"\n";
		return "State : Idle\n";
    }
	virtual void test(int a,int s,int q) const
    {
      std::cout<<a+s-q<<"\n";
    }
	typedef mpl::list< 
		sc::transition< EvIdleTooLong, Idle>,
		sc::transition< EvPlayerWithinRange, Tracing>, 
		sc::transition< EvWithinAttackRange, Attacking > >reactions;
	
};
struct Tracing :Name_test, sc::simple_state< Tracing, NotDeath> {
		Tracing(){ std::cout<<"Tracing\n";};
		virtual ~Tracing() {};
	//	virtual const std::string name () const { return "Tracing"; };
		virtual std::string GetName(int& a) const
		{
			return " State : Tracing \n";
		}
		virtual void test(int a,int s,int q) const
		{
			std::cout<<a+s+q<<"\n";
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
		void change(char);
	
	private:
		FiniteStateMachine FSM;
		irr::scene::IAnimatedMeshSceneNode                   *_monster;
		float _speed; 
	
};

