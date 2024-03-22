#include "gtest/gtest.h"
#include "Laniakea/ECS/PackedArray.h"
#include "Laniakea/ECS/ECS.h"
#include "Laniakea/ECS/ComponentBase.h"
#include <random>

#pragma region TestClasses
struct Vector
{
	Vector ( float x, float y, float z )
			: X ( x ), Y ( y ), Z ( z )
	{};

	Vector operator * ( float rhs ) const
	{ return Vector ( X * rhs, Y * rhs, Z * rhs ); }

	Vector operator + ( const Vector & rhs ) const
	{ return { X + rhs . X, Y + rhs . Y, Z + rhs . Z }; }

	const Vector & operator += ( const Vector & rhs )
	{
		X += rhs . X;
		Y += rhs . Y;
		Z += rhs . Z;
		return * this;
	}


	bool operator != ( const Vector & rhs ) const { return X != rhs . X || Y != rhs . Y || Z != rhs . Z; }
	bool operator == ( const Vector & rhs ) const { return ! (rhs != *this); }

	float X = 0.f;
	float Y = 0.f;
	float Z = 0.f;
};

struct LocationComponent : public ComponentBase
{
	LocationComponent ( EntityHandle owner, Vector location )
			: ComponentBase ( owner ), Location ( location )
	{};
	Vector Location;
};

struct MovementComponent : public ComponentBase
{
	MovementComponent ( EntityHandle owner, float speed, Vector direction )
			: ComponentBase ( owner ), Speed ( speed ), Direction ( direction )
	{};
	float Speed = 0.f;
	Vector Direction;
};

struct HPComponent : public ComponentBase
{
	HPComponent ( EntityHandle owner, int hp, bool isDead = false )
			: ComponentBase ( owner ), HP ( hp ), IsDead ( isDead )
	{};

	void ReceiveDamage ( int damage )
	{
		HP -= damage;
		if ( HP <= 0 ) {
			HP = 0;
			IsDead = true;
			return;
		}
	}

	int HP = 100;
	bool IsDead = false;
};

struct DamageComponent : public ComponentBase
{
	DamageComponent ( EntityHandle owner, EntityHandle entityToDamage, int damage )
			: ComponentBase ( owner ), EntityToDamage ( entityToDamage ), Damage ( damage )
	{};


	void Attack ( HPComponent & other )
	{
		if ( other . GetOwner () != EntityToDamage ) {
			return;
		}
		other . ReceiveDamage ( Damage );
	}

	EntityHandle EntityToDamage;
	int Damage = 10;
};


class DamageSystem : public System
{
public:

	DamageSystem () = default;

	virtual void Run ( ECS & ecs ) override
	{

		// Deferred destroy to not brake m_Entities array.
		std::vector <EntityHandle> DeadEntitiesToRemove;
		std::vector <EntityHandle> DamageComponentsToRemove;
		for ( auto e : m_Entities ) {
			auto & damageComponent = ecs . GetComponent <DamageComponent> ( e );
			auto & hpComponent = ecs . GetComponent <HPComponent> ( damageComponent . EntityToDamage );

			damageComponent . Attack ( hpComponent );

			if ( hpComponent . IsDead ) {
				DamageComponentsToRemove . push_back ( e );
				DeadEntitiesToRemove . push_back ( damageComponent . EntityToDamage );
				continue;
			}
		}
		for ( auto e : DeadEntitiesToRemove ) {
			ecs . RemoveEntity ( e );
		}

		for ( auto e : DamageComponentsToRemove ) {
			ecs . RemoveEntity ( e );
		}
	}
};

class MovementSystem : public System
{
public:

	MovementSystem () = default;

	virtual void Run ( ECS & ecs ) override
	{
		for ( auto e : m_Entities ) {
			auto & movementComponent = ecs . GetComponent <MovementComponent> ( e );
			auto & locationComponent = ecs . GetComponent <LocationComponent> ( e );
			locationComponent . Location += movementComponent . Direction * movementComponent . Speed;
		}
	}
};

class RenderSystem : public System
{
public:

	virtual void Run ( ECS & ) override
	{
	}
};

std::vector <EntityHandle> PrepareECSSystemRun ( ECS & ecs )
{
	auto e1 = ecs . CreateEntity ();
	auto e2 = ecs . CreateEntity ();
	auto e3 = ecs . CreateEntity ();
	auto e4 = ecs . CreateEntity ();

	ecs. RegisterComponent<MovementComponent> ();
	ecs. RegisterComponent <LocationComponent>();
	ecs. RegisterComponent<HPComponent>();
	ecs. RegisterComponent <DamageComponent>();

	ecs . RegisterSystem <MovementSystem, LocationComponent, MovementComponent> ();
	ecs . RegisterSystem <DamageSystem, DamageComponent, HPComponent> ();

	std::vector <EntityHandle> entityHandles = { e1, e2, e3, e4 };
	std::default_random_engine gen;
	std::uniform_real_distribution <float> distribution ( - 50.f, 50.f );

	for ( std::size_t i = 0; i < entityHandles . size (); i ++ ) {
		EntityHandle e = entityHandles[ i ];
		Vector location = { distribution ( gen ), distribution ( gen ), distribution ( gen ) };
		Vector direction = { distribution ( gen ), distribution ( gen ), distribution ( gen ) };
		float speed = distribution ( gen );

		ecs . AddComponent <MovementComponent> ( e, { e, speed, direction } );
		ecs . AddComponent <LocationComponent> ( e, { e, location } );
		ecs . AddComponent <HPComponent> ( e, { e, 100 } );

		EntityHandle entityToDamage = i % 2 == 1 ? e - 1 : e + 1; // Odds attack even, even attack odds
		ecs . AddComponent <DamageComponent> ( e, { e, entityToDamage, 20 } );
	}
	return entityHandles;
}
#pragma endregion
TEST ( PackedArray, PackedArray )
{
	PackedArray <int> data;

	auto id1 = data . Add ( 3 );
	auto id2 = data . Add ( 4 );
	auto id3 = data . Add ( 10 );

	EXPECT_EQ ( data . Size (), size_t ( 3 ) );

	EXPECT_TRUE ( data . Get ( id1 ) == 3 );
	EXPECT_TRUE ( data . Get ( id2 ) == 4 );
	EXPECT_TRUE ( data . Get ( id3 ) == 10 );

	EXPECT_TRUE ( data . RemoveChecked ( id2 ) );

	EXPECT_TRUE ( data . IsValidHandle ( data . GetHandleFromIndex ( 1 ) ) );

	EXPECT_EQ ( data . Size (), size_t ( 2 ) );

	EXPECT_TRUE ( data . Get ( id1 ) == 3 );
	EXPECT_TRUE ( data . Get ( id3 ) == 10 );
	EXPECT_TRUE ( ! data . GetChecked ( id2 ) );

	auto id4 = data . Add ( 25 );

	EXPECT_TRUE ( data . Get ( id1 ) == 3 );
	EXPECT_TRUE ( data . Get ( id3 ) == 10 );
	EXPECT_TRUE ( data . Get ( id4 ) == 25 );

	data . Clear ();

	EXPECT_TRUE ( ! data . GetChecked ( id1 ) );
	EXPECT_TRUE ( ! data . GetChecked ( id3 ) );

	auto id5 = data . Add ( 8 );
	EXPECT_TRUE ( data . Get ( id5 ) == 8 );

	EXPECT_TRUE ( data . RemoveChecked ( id5 ) );
	EXPECT_TRUE ( ! data . GetChecked ( id5 ) );

	std::cout << "(Packed array) tests passed" << std::endl;
}

class EntityComponentSystem : public testing::Test
{

	public:
		ECS ecs;
};

TEST_F ( EntityComponentSystem, ComponentRegistration )
{
	ecs . RegisterComponent <LocationComponent> ();
	EXPECT_TRUE ( ecs . GetIsComponentRegistered <LocationComponent> () );
	EXPECT_TRUE ( ecs . RegisterComponentChecked <MovementComponent> () );
	EXPECT_TRUE ( ecs . RegisterComponentChecked <DamageComponent> () );
	EXPECT_TRUE ( ecs . RegisterComponentChecked <HPComponent> () );
	EXPECT_TRUE ( ! ecs . RegisterComponentChecked <HPComponent> () );
	EXPECT_TRUE ( ecs . GetIsComponentRegistered <HPComponent> () );

}

TEST_F ( EntityComponentSystem, SystemRegistration )
{
	ecs . RegisterSystem <MovementSystem, LocationComponent, MovementComponent> ();
	EXPECT_TRUE ( ecs . GetIsSystemRegistered <MovementSystem> () );
	EXPECT_TRUE ( ! ecs . GetIsSystemRegistered <DamageSystem> () );
	bool Registered = ecs . RegisterSystemChecked <DamageSystem, DamageComponent, HPComponent> ();
	EXPECT_TRUE ( Registered );
	Registered = ecs . RegisterSystemChecked <DamageSystem, HPComponent, DamageComponent> ();
	EXPECT_TRUE ( ! Registered );
	EXPECT_TRUE ( ecs . GetIsSystemRegistered <DamageSystem> () );
}

TEST_F ( EntityComponentSystem, EntityCreation )
{
	EXPECT_TRUE ( ! ecs . GetIsValidEntityHandle ( 0 ) );
	auto e1 = ecs . CreateEntity ();
	auto e2 = ecs . CreateEntity ();

	Entity & en1 = ecs . GetEntity ( e1 );
	auto en2 = ecs . GetEntityChecked ( e2 );
	EXPECT_TRUE ( en1 . GetHandle () == e1 );
	EXPECT_TRUE ( en2 );
	EXPECT_TRUE ( en2 -> get () . GetHandle () == e2 );
	EXPECT_TRUE ( ecs . GetIsValidEntityHandle ( e1 ) );
	EXPECT_TRUE ( ecs . GetIsValidEntityHandle ( e2 ) );
	ecs . RemoveEntity ( e1 );
	EXPECT_TRUE ( ! ecs . GetIsValidEntityHandle ( e1 ) );
	EXPECT_TRUE ( ecs . GetIsValidEntityHandle ( e2 ) );
	EXPECT_TRUE ( ! ecs . RemoveEntityChecked ( e1 ) );
	EXPECT_TRUE ( ecs . RemoveEntityChecked ( e2 ) );
	EXPECT_TRUE ( ! ecs . GetIsValidEntityHandle ( e2 ) );
}

TEST_F ( EntityComponentSystem, ComponentsCreation )
{
	auto e1 = ecs . CreateEntity ();
	auto e2 = ecs . CreateEntity ();
	auto e3 = ecs . CreateEntity ();

	ecs. RegisterComponent <LocationComponent>();
	ecs. RegisterComponent <HPComponent>();

	ecs . AddComponent <LocationComponent> ( e1, { e1, { 0.0f, 0.0f, 1.0f } } );
	EXPECT_TRUE ( ecs . GetEntityHasComponent <LocationComponent> ( e1 ) );
	EXPECT_TRUE ( ecs . GetEntityHasComponentChecked <LocationComponent> ( e1 ) );
	auto ComponentOpt = ecs . GetComponentChecked <LocationComponent> ( e1 );
	EXPECT_TRUE ( ComponentOpt . has_value () );
	LocationComponent & Component = ComponentOpt -> get ();
	Component . Location . X = 10.f;
	auto Component1 = ecs . GetComponent <LocationComponent> ( e1 );
	EXPECT_TRUE ( Component1 . Location . X == 10.f );
	EXPECT_TRUE ( ! ecs . AddComponentChecked <LocationComponent> ( e1, { e1, { 0.0f, 0.0f, 0.0f } } ) );
	EXPECT_TRUE ( ecs . AddComponentChecked <HPComponent> ( e2, { e2, 100 } ) );
	EXPECT_TRUE ( ! ecs . GetEntityHasComponent <HPComponent> ( e1 ) );
	EXPECT_TRUE ( ecs . GetEntityHasComponent <HPComponent> ( e2 ) );
	ecs . AddComponent <LocationComponent> ( e3, { e3, { 10.f, 10.f, 10.f } } );
	ecs . RemoveComponent <LocationComponent> ( e1 );
	EXPECT_TRUE ( ! ecs . GetEntityHasComponent <LocationComponent> ( e1 ) );
	EXPECT_TRUE ( ! ecs . RemoveComponentChecked <LocationComponent> ( e1 ) );
	EXPECT_TRUE ( ecs . RemoveComponentChecked <HPComponent> ( e2 ) );
	EXPECT_TRUE ( ! ecs . GetEntityHasComponent <HPComponent> ( e2 ) );
	ecs . RemoveEntity ( e3 );
	EXPECT_TRUE ( ! ecs . GetEntityHasComponentChecked <LocationComponent> ( e3 ) );
	std::cout << "(Component creation/deletion) tests passed" << std::endl;
}

TEST_F ( EntityComponentSystem, SystemRun )
{
	PrepareECSSystemRun ( ecs );
	// Initialize initial locations
	std::vector <Vector> initialLocations;
	auto locationComponents = ecs . GetComponentsByType <LocationComponent> () . lock ();
	for ( auto & component : * locationComponents )
		initialLocations . push_back ( component . Location );

	// Run system that moves each component in random direction
	EXPECT_TRUE ( ecs . RunSystemChecked <MovementSystem> () );


	// Check if each component location was modified
	for ( size_t i = 0; i < locationComponents -> Size (); i ++ ) {
		auto Handle = locationComponents -> GetHandleFromIndex ( i );
		auto & ModifiedComponent = locationComponents -> GetObject ( Handle );
		EXPECT_TRUE ( ModifiedComponent . Location != initialLocations[ i ] );
	}

	// Initialize initial HP
	std::vector <int> InitialHPArray;
	auto hpComponents = ecs . GetComponentsByType <HPComponent> () . lock ();
	for ( auto & component : * hpComponents )
		InitialHPArray . push_back ( component . HP );

	// Run system that damages each component ( odd entities attack even entities and otherwise )
	EXPECT_TRUE ( ecs . RunSystemChecked <DamageSystem> () );

	// Check if each component HP was modified.
	for ( size_t i = 0; i < hpComponents -> Size (); i ++ ) {
		auto Handle = hpComponents -> GetHandleFromIndex ( i );
		auto & ModifiedComponent = hpComponents -> GetObject ( Handle );
		EXPECT_TRUE ( ModifiedComponent . HP != InitialHPArray[ i ] );
	}

	EXPECT_TRUE ( ! ecs . RunSystemChecked <RenderSystem> () ); // not registered system
	EXPECT_TRUE ( ecs . RegisterSystemChecked <RenderSystem> () );
	EXPECT_TRUE ( ecs . RunSystemChecked <RenderSystem> () );
}

int main ( int argc, char ** argv )
{
	testing::InitGoogleTest( &argc, argv );
	return RUN_ALL_TESTS();
}