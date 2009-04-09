/*
 *  Monster.cpp
 *  FYP
 *
 *  Created by Mr.JJ on 09???????
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Monster.h"
#include "GameEngine.h"
#include "GameWorld.h"
#include "NodeID.h"

static const irr::f64 PI = 3.14159265;

static const irr::c8* MONSTER_MODEL = "media/model/slime08.x";
static const irr::core::vector3df defaultPosition = irr::core::vector3df(-40,0,180);

extern GameEngine* GEngine;

Monster::Monster(GameWorld& gameWorld, irr::video::IVideoDriver& videoDriver)
	:Actor(gameWorld),
	world(gameWorld),
	collisionAnimator(NULL)
{
	irr::scene::ISceneManager& smgr = world.GetSceneManager();
	//_monster = smgr.addAnimatedMeshSceneNode(smgr.getMesh(MONSTER_MODEL), smgr.getRootSceneNode(), ACTOR_ENEMY);
	_monster = smgr.addAnimatedMeshSceneNode(smgr.getMesh(MONSTER_MODEL), smgr.getRootSceneNode());
	_monster->setPosition( defaultPosition );
	_monster->setDebugDataVisible( irr::scene::EDS_BBOX);
	//_monster->setScale(irr::core::vector3df(1,1,1));
	
	//RecreateCollisionResponseAnimator();
	//irr::scene::ITriangleSelector* triangleSelector = world.GetSceneManager().createTriangleSelectorFromBoundingBox( _monster );
	//_monster->setTriangleSelector( triangleSelector );
	//triangleSelector->drop();
	//triangleSelector = NULL;

	irr::scene::ITriangleSelector* meshTriangleSelector = smgr.createOctTreeTriangleSelector( _monster->getMesh(), _monster );
	check(meshTriangleSelector);
	_monster->setTriangleSelector( meshTriangleSelector );
	world.GetLevelTriangleSelector().addTriangleSelector(meshTriangleSelector);
	meshTriangleSelector->drop();
	meshTriangleSelector = NULL;

	FSM.initiate();
	original = defaultPosition;
	pos = defaultPosition;
	target = pos;
	moved = false;
	health = 100;
	timeout = 5.0;
	mon_timer = new boost::timer();
	attack_timer = new boost::timer();
	death_timer =  new boost::timer();
	death_timer->restart();
	mon_timer->restart();
	attack_timer->restart();
}


//this function is used for jumping
static irr::f32 floating( irr::f32 delta, irr::s32 range )
{
	static irr::f32 total_delta = 0;
	total_delta += delta;
	//std::cout << "delta:                " << delta << std::endl;
	//std::cout << "total_delta:                " << total_delta << std::endl;
	//return range * sin(total_delta) + 1;
	return sin(total_delta*5);
}
void Monster::update(Player& _player, irr::f32 delta)
{
	health-=1;
	//CheckActorPosition();
	//std::cout<<world.GetActors().size()<<" size \n";
	pos= _monster->getAbsolutePosition();
	//std::cout<<"origin: "<<_player.GetNodePosition().getDistanceFrom(original)<<"\n";
	//std::cout<<"pos : "<<_player.GetNodePosition().getDistanceFrom(pos)<<"\n";
	//std::cout<<_player.GetNodePosition().X<<" "<<_player.GetNodePosition().Y<<" "<<_player.GetNodePosition().Z<<"\n";
	//std::cout<<pos.X<<" "<<pos.Y<<" "<<pos.Z<<"\n";
	if(health <= 0)
	{
		//Death
	
		if(FSM.GetName()!="Death"){
			FSM.process_event( EvDie());
			FSM.reaction(_monster, _player,target);
			irr::scene::ISceneManager& smgr = world.GetSceneManager();
			
			sparking= new ParticleSystemEngine(&smgr, pos, irr::core::vector3df(2,2,2),
											   irr::core::aabbox3d<irr::f32>(-7,0,-7,7,1,7) );
			sparking->CreateMeshEmitter(smgr.getMesh("media/model/slime08.x"),irr::core::vector3df(0.0f,0.06f,0.0f),
										20,50,200,700, GEngine->GetDriver().getTexture("media/shader/fire.bmp"));
			death_timer->restart();
		}else if(death_timer->elapsed() > 2.0){
		
			sparking->resetEmitter();
		}
		
		
		
		
	}else if(_player.GetNodePosition().getDistanceFrom(pos)< 30.0f)
	{
		//std::cout<<"Attack_timer: "<<attack_timer->elapsed()<<"\n";
		if(FSM.GetName() != "Attacking"){
			FSM.process_event( EvWithinAttackRange());
			if(attack_timer->elapsed() > timeout){
				attack_timer->restart();
				FSM.reaction(_monster, _player,target);
			}
		}else{

			if(attack_timer->elapsed() > timeout){
				//	std::cout<<"Mon_timer:------------"<<"\n";
				attack_timer->restart();
				FSM.reaction(_monster, _player,target);			
			}
		}
	}
	else if( _player.GetNodePosition().getDistanceFrom(original)< 120.0f
			|| _player.GetNodePosition().getDistanceFrom(pos)< 80.0f )
	{
		mon_timer->restart();
		irr::core::vector3df targetPos =_monster->getPosition()+((_player.GetNodePosition() - _monster->getPosition())/100.0f);
		CheckActorPosition(targetPos, _player);
		
		if( targetPos.getDistanceFrom(original) < 120.0f )
		{
			//Tracing mode
			//if(FSM.GetName() != "Tracing"){
			if(FSM.GetName() == "Attacking")
				FSM.process_event(EvFiniteStateMachineOutOfRange());
			FSM.process_event( EvPlayerWithinRange());
			//irr::core::vector3df targetPos = _monster->getPosition()+((_player.GetNodePosition() - _monster->getPosition())/42.5f);
			//if(targetPos !=  _monster->getPosition()+((_player.GetNodePosition() - _monster->getPosition())/42.5f) )
			target = targetPos;

			FSM.reaction(_monster, _player,target);
			pos = _monster->getPosition();
			target = pos;


		}
		else
		{
			FSM.process_event( EvFiniteStateMachineOutOfRange());
			FSM.reaction(_monster, _player,target);
		}

		//for jumping
		irr::core::vector3df offset = irr::core::vector3df( 0, floating( delta, 1)*0.5, 0);
		_monster->setPosition(_monster->getAbsolutePosition()+offset);
		_monster->setRotation(_monster->getRotation()+offset);


	}else if ( pos.getDistanceFrom(original) > 120.0f){
			//std::cout<<"Out of range !!\n";


	}else{
			//Idle	
			//std::cout<<"Mon_timer: "<<mon_timer->elapsed()<<"\n";
			//irr::u32 current = mon_timer->getTime();
			if( FSM.GetName() != "Idle" )
			{
				mon_timer->restart();
				//std::cout<<"Mon_timer:Restart "<<"\n";

				FSM.process_event( EvFiniteStateMachineOutOfRange());
				FSM.reaction(_monster, _player,target);

			}
			else
			{
				if( mon_timer->elapsed() > timeout )
				{
					if( (target - pos) < irr::core::vector3df(10.0, 0.0, 10.0) || target ==pos||mon_timer->elapsed() > 7.0  )
					{
						if(!moved )
						{

							srand ( time(NULL) );
							float x = ((float)(rand() % 20 + 1))-10;
							float z = ((float)(rand() % 20 + 1))-10;
							float y = _monster->getPosition().Y;
							target.X = pos.X+x;
							target.Y = y;
							target.Z = pos.Z+z;
							irr::core::vector3df direction = pos-target;
							_monster->setRotation(direction.getHorizontalAngle());
							FSM.IdleTooLong(_monster,_player, target);
							pos = _monster->getPosition();
						}
						else
						{
							moved = false;
							mon_timer->restart();

						}

					}
					else
					{
						//FSM.process_event( EvFiniteStateMachineOutOfRange());
						FSM.IdleTooLong(_monster,_player, target);
						pos = _monster->getPosition();
						target=pos;
						moved = true;
					}
				}
			}
		}
	}

void Monster::RecreateCollisionResponseAnimator()
{
	// drop the current collision response animator
	if( collisionAnimator )
	{
		_monster->removeAnimator( collisionAnimator );
		collisionAnimator->drop();
		collisionAnimator = NULL;
	}

	// setup torso collision with the world
	irr::core::aabbox3df box = _monster->getMesh()->getMesh(0)->getBoundingBox();
	irr::core::vector3df radius = box.MaxEdge - box.getCenter();

	collisionAnimator = world.GetSceneManager().createCollisionResponseAnimator(
			&world.GetLevelTriangleSelector(), _monster, radius, irr::core::vector3df(0,-.08f,0), // gravity
			irr::core::vector3df(0, 0, 0), // ellipsoid translation
			0.0001f); // sliding value

	_monster->addAnimator(collisionAnimator);
}

void Monster::ReceiveDamage(irr::f32 damage){
	health -= damage;
		std::cout<<"Health: "<<health<<std::endl;
}


void  Monster::Tick(irr::f32 delta){
	update(world.GetCurrentPlayer(), delta);
}

void Monster::ReSetPosition(irr::core::vector3df NewPosition){
	original = NewPosition;
	pos = NewPosition;
	target = NewPosition;
	_monster->setPosition(NewPosition); 
	_monster->updateAbsolutePosition();
	//std::cout<<original.X<<" "<<original.Y<<" "<<original.Z<<"\n";
	pos = _monster->getAbsolutePosition();
	//std::cout<<pos.X<<" "<<pos.Y<<" "<<pos.Z<<"\n";


	//_monster->setScale(irr::core::vector3df(0.5,0.5,0.5));
	_monster->setLoopMode(false);
	
	// setup player collision with the world
	/*RecreateCollisionResponseAnimator();

	irr::scene::ITriangleSelector* triangleSelector = world.GetSceneManager().createOctTreeTriangleSelectorFromBoundingBox( _monster );
	_monster->setTriangleSelector( triangleSelector );
	triangleSelector->drop();
	triangleSelector = NULL;*/
}

void Monster::CheckActorPosition(irr::core::vector3df& target, Player& _player){
	static int last_move = 0;

	irr::core::array<irr::scene::ISceneNode*> outNodes;
	irr::scene::ISceneManager& smgr = world.GetSceneManager();
	// smgr.getSceneNodesFromType( irr::scene::ESNT_MESH, outNodes );
	float min = 9999.99;
	irr::core::vector3df next_pos = target;

	irr::core::array<irr::scene::IMeshSceneNode*>& blocks = world.GetBlocking();
	irr::u32 blocking_size = blocks.size();

	for(irr::u32 i = 0; i < blocking_size; ++i){
		irr::scene::IMeshSceneNode* meshNode = blocks[i];
		if(min  > pos.getDistanceFrom(meshNode->getPosition() ))
			min = pos.getDistanceFrom(meshNode->getPosition() );
		//std::cout<< pos.getDistanceFrom(meshNode->getPosition() )<<"\n";
		if(pos.getDistanceFrom(meshNode->getPosition() ) < 50.0){
			//std::cout<< pos.getDistanceFrom(meshNode->getPosition() )<<"\n";
			irr::core::vector3df directionM = meshNode->getPosition()-_player.GetNodePosition();
			irr::core::vector3df directionT = meshNode->getPosition() - _monster->getPosition();
			float angle = directionM.dotProduct(directionT);
			angle = angle/(directionM.getLength() * directionT.getLength());
			angle = acos(angle)*180.0/ PI;
			//std::cout<<"angle: "<<floor(angle)<<"\n";

			if(floor(angle) > 60 ){
				//std::cout<<"-------------------------\n";
				bool found = false;
				float mov_x, mov_z;
				if(_player.GetNodePosition().X > _monster->getPosition().X)
					mov_x = 5.0;
				else
					mov_x = -5.0;
				if(_player.GetNodePosition().Z > _monster->getPosition().Z)
					mov_z = 5.0;
				else
					mov_z = -5.0;
				next_pos = target;
				if(last_move != 0){
					switch (last_move){
						case 1 : 
							if(meshNode->getPosition().Z > next_pos.Z)
								next_pos.Z-=mov_z;
							else next_pos.Z+=mov_z;
							last_move = 0;
							break;
						case 2 : if(meshNode->getPosition().X > next_pos.X)
								 next_pos.X-=mov_x;
							 else next_pos.X+=mov_x;
							 last_move = 0;
							 break;
						case 3 : if(meshNode->getPosition().Z > next_pos.Z)
								 next_pos.Z-=mov_z;
							 else next_pos.Z+=mov_z;
							 last_move = 0;
							 break;
						case 4 : if(meshNode->getPosition().X > next_pos.X)
								 next_pos.X-=mov_x;
							 else next_pos.X+=mov_x;
							 last_move = 0;
							 break;
					}
				}
				else{

					irr::core::vector3df next_pos1 = target;
					next_pos1.X+=mov_x;
					if(next_pos.getDistanceFrom(meshNode->getPosition() ) > 40.0){
						found = true;
					}
					if(next_pos.getDistanceFrom(_player.GetNodePosition()) > next_pos1.getDistanceFrom(_player.GetNodePosition())){
						next_pos = next_pos1;
						last_move = 1;
						//std::cout<<"PATH FOUND_X\n";
					}

					irr::core::vector3df next_pos2 = target;
					next_pos2.Z +=mov_z;
					if(next_pos.getDistanceFrom(meshNode->getPosition() ) > 40.0){
						found = true;
					}
					if(next_pos.getDistanceFrom(_player.GetNodePosition()) > next_pos2.getDistanceFrom(_player.GetNodePosition())){
						next_pos = next_pos2;
						last_move = 2;
						//std::cout<<"PATH FOUND_Z\n";
					}

					irr::core::vector3df next_pos3 = target;
					mov_x=-mov_x;
					mov_z=-mov_z;
					next_pos3 = target;
					next_pos3.X+=mov_x;
					if(next_pos.getDistanceFrom(meshNode->getPosition() ) > 40.0){
						found = true;


					}
					if(next_pos.getDistanceFrom(_player.GetNodePosition()) > next_pos3.getDistanceFrom(_player.GetNodePosition())){
						next_pos = next_pos3;
						last_move = 3;
						//std::cout<<"PATH FOUND_X2\n";
					}

					irr::core::vector3df next_pos4 = target;

					next_pos4.Z +=mov_z;
					if(next_pos.getDistanceFrom(meshNode->getPosition() ) > 40.0){
						found = true;
					}
					if(next_pos.getDistanceFrom(_player.GetNodePosition()) > next_pos4.getDistanceFrom(_player.GetNodePosition())){
						next_pos = next_pos4;
						last_move = 4;
						//std::cout<<"PATH FOUND_Z2\n";
					}
				}
			}
			else
				last_move=0;

			//	std::cout<<angle<<"\n";
			//if( target.getDistanceFrom(meshNode->getPosition() ) < 40.0)
			//	std::cout<<"GOING TO BE BLOACKED \n";
			//std::cout<<"BLOCKED\n";

			//std::cout<<pos.getDistanceFrom(meshNode->getPosition() )<<"\n";
		}
	}

	//std::cout<<"min: "<<min<<"\n";
	next_pos.Y = _monster->getPosition().Y;
	target = next_pos;
}
