/*
 *  Monster.cpp
 *  FYP
 *
 *  Created by Mr.JJ on 09年2月9日.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Monster.h"

Monster::Monster(irr::scene::IAnimatedMeshSceneNode* source, irr::core::vector3df position, irr::core::vector3df scale, float speed)
:_monster(source),_speed(speed){
	_monster->setLoopMode(false);
	_monster->setPosition(position);
	_monster->setScale(scale);
	_monster->setMaterialFlag(irr::video::EMF_LIGHTING, true);
	FSM.initiate();
	original = position; 
	pos = position;
	Health = 100;
	//FSM.test() = "TEST";
}

void Monster::change(char c, Player* _player){
		int num =1;
		switch (c){
			case 't':
			{
				FSM.process_event ( EvDie() );
				FSM.reaction(_monster, _player);
				break;
			}
			case 'w':
			{
				FSM.process_event ( EvPlayerWithinRange() );
				FSM.reaction(_monster,_player);
				break;
			}
			case 'a':
			{
				FSM.process_event ( EvWithinAttackRange() );
				FSM.reaction(_monster, _player);
				break;
			}
			case 'o':
			{
				FSM.process_event ( EvOutOfAttackRange() );
				FSM.reaction(_monster, _player);
				break;
			}
			case 'm':
			{
				std::cout<<"Here1\n";
				//FSM.test(1,2,3);
				
				std::cout<<FSM.GetName()<<"\n";
				std::cout<<num<<std::endl;
				break;
			}
		}
	}


void Monster::update(Player* _player){

	std::cout<<_player->getPosition().getDistanceFrom(pos)<<"\n";
	if(Health <= 0){//Death
		FSM.process_event( EvDie());
		FSM.reaction(_monster, _player);
	}else if( _player->getPosition().getDistanceFrom(pos)< 4.0f ){
		//Tracing mode
		FSM.process_event( EvPlayerWithinRange());
		FSM.reaction(_monster, _player);
		pos = _monster->getPosition();
		
	}else{//Idle	
		FSM.process_event( EvFiniteStateMachineOutOfRange());
		FSM.reaction(_monster, _player);
	}
	

}

void Monster::Hit(int damage){
	Health-=damage;
	std::cout<<Health<<std::endl;
}
