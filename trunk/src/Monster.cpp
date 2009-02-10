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
	_monster->setPosition(position);
	_monster->setScale(scale);
	_monster->setMaterialFlag(irr::video::EMF_LIGHTING, true);
	FSM.initiate();
	//FSM.test() = "TEST";
}

void Monster::change(char c){
		int num =1;
		switch (c){
			case 't':
			{
				FSM.process_event ( EvDie() );
				FSM.test(1,2,3);
				break;
			}
			case 'w':
			{
				FSM.process_event ( EvPlayerWithinRange() );
				FSM.test(1,2,3);
				break;
			}
			case 'a':
			{
				FSM.process_event ( EvWithinAttackRange() );
				FSM.test(1,2,3);
				break;
			}
			case 'o':
			{
				FSM.process_event ( EvOutOfAttackRange() );
				FSM.test(1,2,3);
				break;
			}
			case 'm':
			{
				std::cout<<"Here1\n";
				//FSM.test(1,2,3);
				
				std::cout<<FSM.GetName(num)<<"\n";
				std::cout<<num<<std::endl;
				break;
			}
		}
	}

