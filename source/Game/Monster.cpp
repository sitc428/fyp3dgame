/*
 *  Monster.cpp
 *  FYP
 *
 *  Created by Mr.JJ on 09???????
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
//1-30
//31-60
#include "Monster.hpp"
#include "GameEngine.hpp"
#include "GameWorld.hpp"
#include "NodeID.hpp"
#include "MainCharacter.hpp"
#include "ProgressCircle.hpp"
//#include "shader.hpp"
#include "ShaderFactory.hpp"

static const irr::c8* MONSTER_MODEL = "media/model/slime.x";
static const irr::c8* BOSS_MODEL = "media/model/kingslime.x";
static const irr::core::vector3df defaultPosition = irr::core::vector3df(-40,0,180);

static const irr::u32		MONSTER_ANIMATION_WALK_FORWARD_START = 1;
static const irr::u32		MONSTER_ANIMATION_WALK_FORWARD_END = 30;
static const irr::u32		MONSTER_ANIMATION_ATTACK1_START = 31;
static const irr::u32		MONSTER_ANIMATION_ATTACK1_END = 60;


Monster::Monster(GameEngine& gameEngine, GameWorld& gameWorld, irr::s32 exp, irr::s32 hp, irr::s32 attk, irr::s32 def, irr::s32 mattk, irr::s32 mdef, ItemCollection monItemBox,irr::core::vector3df NewPosition, irr::core::stringw type, irr::u32 money)
	: Actor(gameEngine, gameWorld),
	collisionAnimator(NULL),
	_exp(exp),
	_attk(attk),
	_def(def),
	_mattk(mattk),
	_mdef(mdef),
	_monItemBox(monItemBox),
	_money(money),
	health(hp),
	maxhealth(health)
{
	irr::scene::ISceneManager& smgr = world.GetSceneManager();
	irr::video::IVideoDriver& driver = GEngine.GetDriver();
	if(type=="Type1"){
		Shader* shader = GEngine.GetShaderFactory().createShader( "media/shader/Monster_shader.vert", "media/shader/Monster_shader.frag", 2 , irr::video::EMT_TRANSPARENT_ADD_COLOR );
		_monster = smgr.addAnimatedMeshSceneNode(smgr.getMesh(MONSTER_MODEL), smgr.getRootSceneNode());
		if(GEngine.GetShaderFactory().ShaderAvailable())
			_monster->setMaterialType((irr::video::E_MATERIAL_TYPE) shader->GetShaderMaterial() );
		else
			_monster->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
		_monster->setMaterialTexture(0, driver.getTexture("media/model/slime.tga"));
		_monster->setMaterialTexture(1, driver.getTexture("media/model/black.png"));
		timeout = 5.0;
		_monster->setScale(irr::core::vector3df(1,0.554,1));
	}else if( type == "Type2"){
		
			Shader* shader = GEngine.GetShaderFactory().createShader( "media/shader/Monster_shader_2.vert", "media/shader/Monster_shader_2.frag", 2 , irr::video::EMT_TRANSPARENT_ADD_COLOR );
			_monster = smgr.addAnimatedMeshSceneNode(smgr.getMesh(MONSTER_MODEL), smgr.getRootSceneNode());
		
			if(GEngine.GetShaderFactory().ShaderAvailable())
				_monster->setMaterialType((irr::video::E_MATERIAL_TYPE) shader->GetShaderMaterial() );
			else
				_monster->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
		
			_monster->setMaterialTexture(0, driver.getTexture("media/model/slime2.tga"));
			_monster->setMaterialTexture(1, driver.getTexture("media/model/black.png"));
			timeout = 5.0;
			_monster->setScale(irr::core::vector3df(1,0.554,1));
	}else if( type == "Type3"){
		
		Shader* shader = GEngine.GetShaderFactory().createShader( "media/shader/Monster_shader_3.vert", "media/shader/Monster_shader_3.frag", 2 , irr::video::EMT_TRANSPARENT_ADD_COLOR );
		_monster = smgr.addAnimatedMeshSceneNode(smgr.getMesh(MONSTER_MODEL), smgr.getRootSceneNode());
		
		if(GEngine.GetShaderFactory().ShaderAvailable())
			_monster->setMaterialType((irr::video::E_MATERIAL_TYPE) shader->GetShaderMaterial() );
		else
			_monster->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
		
		_monster->setMaterialTexture(0, driver.getTexture("media/model/slime3.tga"));
		_monster->setMaterialTexture(1, driver.getTexture("media/model/black.png"));
		_monster->setScale(irr::core::vector3df(1,0.554,1));
		timeout = 5.0;
	}else if( type == "Type4"){
		
		Shader* shader = GEngine.GetShaderFactory().createShader( "media/shader/Monster_shader_4.vert", "media/shader/Monster_shader_4.frag", 2 , irr::video::EMT_TRANSPARENT_ADD_COLOR );
		_monster = smgr.addAnimatedMeshSceneNode(smgr.getMesh(MONSTER_MODEL), smgr.getRootSceneNode());
		
		if(GEngine.GetShaderFactory().ShaderAvailable())
			_monster->setMaterialType((irr::video::E_MATERIAL_TYPE) shader->GetShaderMaterial() );
		else
			_monster->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
		
		_monster->setMaterialTexture(0, driver.getTexture("media/model/slime1.tga"));
		_monster->setMaterialTexture(1, driver.getTexture("media/model/black.png"));
		_monster->setScale(irr::core::vector3df(1,0.554,1));
		timeout = 5.0;
	} if( type == "Boss"){
		
		Shader* shader = GEngine.GetShaderFactory().createShader( "media/shader/Monster_shader_Boss.vert", "media/shader/Monster_shader_Boss.frag", 2 , irr::video::EMT_TRANSPARENT_ADD_COLOR );
		_monster = smgr.addAnimatedMeshSceneNode(smgr.getMesh(BOSS_MODEL), smgr.getRootSceneNode());
		
		if(GEngine.GetShaderFactory().ShaderAvailable())
			_monster->setMaterialType((irr::video::E_MATERIAL_TYPE) shader->GetShaderMaterial() );
		else
			_monster->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
		_monster->setScale(irr::core::vector3df(2.7,1.5,2.7));
		_monster->setMaterialTexture(0, driver.getTexture("media/model/slime1.tga"));
		_monster->setMaterialTexture(1, driver.getTexture("media/model/black.png"));
		timeout = 1.0;
		
	}
	
	irr::scene::ITriangleSelector* meshTriangleSelector = smgr.createOctTreeTriangleSelector( _monster->getMesh(), _monster );
	check(meshTriangleSelector);
	_monster->setTriangleSelector( meshTriangleSelector );
	world.GetLevelTriangleSelector().addTriangleSelector(meshTriangleSelector);
	meshTriangleSelector->drop();
	meshTriangleSelector = NULL;

	FSM = new FiniteStateMachine;

	FSM->initiate();
	original = defaultPosition;
	pos = defaultPosition;
	target = pos;
	moved = false;
	
	mon_timer = new boost::timer();
	attack_timer = new boost::timer();
	death_timer =  new boost::timer();
	death_timer->restart();
	mon_timer->restart();
	attack_timer->restart();
	Type= type;
	
	
	original = NewPosition;
	pos = NewPosition;
	target = NewPosition;
	_monster->setPosition(NewPosition);
	_monster->updateAbsolutePosition();
	RecreateCollisionResponseAnimator();
	
	//std::cout<<original.X<<" "<<original.Y<<" "<<original.Z<<"\n";
	pos = _monster->getAbsolutePosition();


	_monster->setLoopMode(false);
	_monster->setCurrentFrame( MONSTER_ANIMATION_WALK_FORWARD_START );
	_monster->setFrameLoop(1, 30 );
	_monster->setLoopMode(true);
	
	
	
	
	
	healthBar = new ProgressCircle( _monster, &(world.GetSceneManager()), -1, world.GetSceneManager().getSceneCollisionManager(), 100, 10, 100, irr::core::vector3df(0, 25, 0));
	healthBar->setVisible( false );
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
	
	//std::cout<<"origin: "<<_player.GetNodePosition().getDistanceFrom(original)<<"\n";
	//std::cout<<"pos : "<<_player.GetNodePosition().getDistanceFrom(pos)<<"\n";
	//std::cout<<_player.GetNodePosition().X<<" "<<_player.GetNodePosition().Y<<" "<<_player.GetNodePosition().Z<<"\n";
	//std::cout<<pos.X<<" "<<pos.Y<<" "<<pos.Z<<"\n";
	if(health <= 0)
	{
		_monster->setLoopMode(false);
		//Death;
		if( FSM->GetName() != "Death" )
		{
			std::cout << "Player Level: " << ((MainCharacter&)world.GetCurrentPlayer()).GetLevel() << std::endl;
		//+ player exp
		((MainCharacter&)world.GetCurrentPlayer()).SetEXP(
			((MainCharacter&)world.GetCurrentPlayer()).GetEXP()+
			_exp);
		

		//+$$$
		((MainCharacter&)world.GetCurrentPlayer()).SetMoney(
			((MainCharacter&)world.GetCurrentPlayer()).GetMoney() + _money);
		//+item
		ItemCollection playerTmpBox = ((MainCharacter&)world.GetCurrentPlayer()).GetItemBox();
		for (int i=0; i<_monItemBox.size(); i++)
		{
			bool newItem = false;
			for (int j=0; j<playerTmpBox.size(); j++)
			{
				if (_monItemBox[i].first->getItemName() == playerTmpBox[j].first->getItemName())
				{
					playerTmpBox[j].second += _monItemBox[i].second;
					newItem = false;
					break;
				}
				else
				{
					newItem = true;
				}
			}
			if (newItem)
			{
				playerTmpBox.push_back(std::make_pair(_monItemBox[i].first, _monItemBox[i].second));
			}
		}
		((MainCharacter&)world.GetCurrentPlayer()).SetItemBox(playerTmpBox);

		//+level
		irr::s32 playerLevel = ((MainCharacter&)world.GetCurrentPlayer()).GetLevel();
		irr::s32 playerEXP = ((MainCharacter&)world.GetCurrentPlayer()).GetEXP();


			FSM->process_event( EvDie() );
			FSM->reaction(_monster, _player,target, this);
			irr::scene::ISceneManager& smgr = world.GetSceneManager();
			pos.Y=8.0;
			sparking= new ParticleManager(&smgr, pos, irr::core::vector3df(2,2,2),
											   irr::core::aabbox3d<irr::f32>(-7,0,-7,7,1,7) );
			if(Type=="Type1"||Type=="Type2"||Type=="Type3"||Type=="Type4"){
				sparking->CreateMeshEmitter(smgr.getMesh("media/model/slime08.x"),irr::core::vector3df(0.0f,0.06f,0.0f),
										20,50,200,700, GEngine.GetDriver().getTexture("media/model/particlewhite.bmp"));
			
				
			}else if(Type=="Boss"){
				
				world.requestGameVictory();
			}
			death_timer->restart();

			/*irr::core::array<Actor*> actors = world.GetActors();
			int temp = actors.binary_search( this );
				actors.erase(temp, 1);*/

		}else if(death_timer->elapsed() > 2.0){
		
			sparking->resetEmitter();
			state = state_ACTOR_DEAD;
		}	
		
	}else if(	(Type=="Type1"||Type=="Type2"||Type=="Type3"||Type=="Type4")&&_player.GetNodePosition().getDistanceFrom(pos)< 30.0f||
				Type == "Boss" && _player.GetNodePosition().getDistanceFrom(pos)< 50.0f
			 )
	{
		
		//std::cout<<"Attack_timer: "<<attack_timer->elapsed()<<"\n";
		if(FSM->GetName() != "Attacking"){
			FSM->process_event( EvWithinAttackRange());
			if(attack_timer->elapsed() > timeout){
				attack_timer->restart();
				FSM->reaction(_monster, _player,target, this);
				_monster->setLoopMode(false);
				_monster->setCurrentFrame( MONSTER_ANIMATION_ATTACK1_START );
				_monster->setFrameLoop( MONSTER_ANIMATION_ATTACK1_START,MONSTER_ANIMATION_ATTACK1_END );
				_monster->setLoopMode(true);
			}
		}else{

			if(attack_timer->elapsed() > timeout){
				//	std::cout<<"Mon_timer:------------"<<"\n";
				attack_timer->restart();
				_monster->setLoopMode(false);
				_monster->setCurrentFrame( MONSTER_ANIMATION_WALK_FORWARD_START );
				_monster->setFrameLoop( MONSTER_ANIMATION_ATTACK1_START,MONSTER_ANIMATION_ATTACK1_END );
				_monster->setLoopMode(true);
				FSM->reaction(_monster, _player,target, this);			
			}else _monster->setLoopMode(false);
		}
	}
	else if( (Type=="Type1"||Type=="Type2"||Type=="Type3"||Type=="Type4")&&_player.GetNodePosition().getDistanceFrom(original)< 160.0f
			|| (Type=="Type1"||Type=="Type2"||Type=="Type3"||Type=="Type4")&&_player.GetNodePosition().getDistanceFrom(pos)< 100.0f ||
			( Type == "Boss" && _player.GetNodePosition().getDistanceFrom(original)< 200.0f || Type == "Boss" && _player.GetNodePosition().getDistanceFrom(pos)< 140.0f )
		)
	{
		mon_timer->restart();
		if(FSM->GetName() != "Tracing"){
			_monster->setLoopMode(false);
			_monster->setCurrentFrame( MONSTER_ANIMATION_WALK_FORWARD_START );
			_monster->setFrameLoop(1, 30 );
			_monster->setLoopMode(true);
		}
		irr::core::vector3df targetPos;
		if( Type=="Boss")
			targetPos =_monster->getPosition()+((_player.GetNodePosition() - _monster->getPosition())/50.0f);
		else 
			targetPos =_monster->getPosition()+((_player.GetNodePosition() - _monster->getPosition())/100.0f);
		targetPos.Y = -10.0;
		CheckActorPosition(targetPos, _player);
		
		if( (Type=="Type1"||Type=="Type2"||Type=="Type3"||Type=="Type4")&& targetPos.getDistanceFrom(pos) < 100.0f ||
			Type == "Boss" && _player.GetNodePosition().getDistanceFrom(pos)< 140.0f
			)
		{
			
			//Tracing mode
			//if(FSM->GetName() != "Tracing"){
			if(FSM->GetName() == "Attacking")
				FSM->process_event(EvFiniteStateMachineOutOfRange());
			FSM->process_event( EvPlayerWithinRange());
			//irr::core::vector3df targetPos = _monster->getPosition()+((_player.GetNodePosition() - _monster->getPosition())/42.5f);
			//if(targetPos !=  _monster->getPosition()+((_player.GetNodePosition() - _monster->getPosition())/42.5f) )
			target = targetPos;
			target.Y=-10.0;
			FSM->reaction(_monster, _player,target,this);
			pos = _monster->getPosition();
			target = pos;


			//for jumping
			/*
			irr::core::vector3df offset = irr::core::vector3df( 0, floating( delta, 1)*0.5, 0);
			if((_monster->getAbsolutePosition()+offset).Y < 0 ){
				irr::core::vector3df v = _monster->getAbsolutePosition()+offset;
				v.Y = 0.0;
				_monster->setPosition(v);
			}else 
				_monster->setPosition(_monster->getAbsolutePosition()+offset);
			_monster->setRotation(_monster->getRotation()+offset);
			 */
			
		}
		else
		{
			FSM->process_event( EvFiniteStateMachineOutOfRange());
			FSM->reaction(_monster, _player,target, this);
		}

				//pos= _monster->getAbsolutePosition() - offset;

	}else{
			//Idle	
			//std::cout<<"Mon_timer: "<<mon_timer->elapsed()<<"\n";
			//irr::u32 current = mon_timer->getTime();
			_monster->setLoopMode(false);
			if( FSM->GetName() != "Idle" )
			{
				mon_timer->restart();
				//std::cout<<"Mon_timer:Restart "<<"\n";

				FSM->process_event( EvFiniteStateMachineOutOfRange());
				FSM->reaction(_monster, _player,target, this);

			}
			else
			{
				if( mon_timer->elapsed() > 2.0 )
				{
					if( (target - pos) < irr::core::vector3df(10.0, -10.0, 10.0) || target ==pos||mon_timer->elapsed() > 7.0  )
					{
						if(!moved )
						{

							srand ( time(NULL) );
							float x = ((float)(rand() % 20 + 1))-10;
							float z = ((float)(rand() % 20 + 1))-10;
							float y = _monster->getPosition().Y;
							target.X = pos.X+x;
							target.Y = -10.0;
							target.Z = pos.Z+z;
							irr::core::vector3df direction = pos-target;
							_monster->setRotation(direction.getHorizontalAngle());
							FSM->IdleTooLong(_monster,_player, target);
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
						//FSM->process_event( EvFiniteStateMachineOutOfRange());
						FSM->IdleTooLong(_monster,_player, target);
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
	if( health - damage > 0 )
		health -= damage;
	else
		health = 0;

	healthBar->setProgress( 100 * ( health / maxhealth ) );

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
//	RecreateCollisionResponseAnimator();

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
	float meshSize = 40.0;
	float angleX = 60.0;

	irr::core::array<irr::scene::IMeshSceneNode*>& blocks = world.GetBlocking();
	irr::u32 blocking_size = blocks.size();

	for(irr::u32 i = 0; i < blocking_size; ++i){
		irr::scene::IMeshSceneNode* meshNode = blocks[i];
		if(min  > pos.getDistanceFrom(meshNode->getPosition() ))
			min = pos.getDistanceFrom(meshNode->getPosition() );
		if(meshNode->getID() == NODE_ID_SCENE1_HOUSE || meshNode->getID() == NODE_ID_SCENE1_HOUSE2){
			meshSize = 120.0;
			angleX = 20.0;
		}else{
			meshSize = 40.0;
			angleX = 60.0;
		}
		//std::cout<< pos.getDistanceFrom(meshNode->getPosition() )<<"\n";
		if(pos.getDistanceFrom(meshNode->getPosition() ) < meshSize){
			//std::cout<< pos.getDistanceFrom(meshNode->getPosition() )<<"\n";
			irr::core::vector3df directionM = meshNode->getPosition()-_player.GetNodePosition();
			irr::core::vector3df directionT = meshNode->getPosition() - _monster->getPosition();
			float angle = directionM.dotProduct(directionT);
			angle = angle/(directionM.getLength() * directionT.getLength());
			angle = acos(angle)*180.0/ PI;
			//std::cout<<"angle: "<<floor(angle)<<"\n";

			if(floor(angle) > angleX && directionT.getLength() <= directionM.getLength() ){
				//std::cout<<"-------------------------\n";
				bool found = false;
				float mov_x, mov_z;
				if(_player.GetNodePosition().X > _monster->getPosition().X)
					mov_x = 2.0;
				else
					mov_x = -2.0;
				if(_player.GetNodePosition().Z > _monster->getPosition().Z)
					mov_z = 2.0;
				else
					mov_z = -2.0;
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
					if(next_pos.getDistanceFrom(meshNode->getPosition() ) > meshSize){
						found = true;
					}
					if(next_pos.getDistanceFrom(_player.GetNodePosition()) > next_pos1.getDistanceFrom(_player.GetNodePosition())){
						next_pos = next_pos1;
						last_move = 1;
						//std::cout<<"PATH FOUND_X\n";
					}

					irr::core::vector3df next_pos2 = target;
					next_pos2.Z +=mov_z;
					if(next_pos.getDistanceFrom(meshNode->getPosition() ) > meshSize){
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
					if(next_pos.getDistanceFrom(meshNode->getPosition() ) > meshSize){
						found = true;


					}
					if(next_pos.getDistanceFrom(_player.GetNodePosition()) > next_pos3.getDistanceFrom(_player.GetNodePosition())){
						next_pos = next_pos3;
						last_move = 3;
						//std::cout<<"PATH FOUND_X2\n";
					}

					irr::core::vector3df next_pos4 = target;

					next_pos4.Z +=mov_z;
					if(next_pos.getDistanceFrom(meshNode->getPosition() ) > meshSize){
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

void Monster::setHealthBarVisible( bool isVisible )
{
	healthBar->setVisible( isVisible );
}