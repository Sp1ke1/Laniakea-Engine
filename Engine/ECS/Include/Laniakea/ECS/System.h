#pragma once

#include "ObjectManager.h"
#include "Entity.h"
#include <algorithm>

// Forward declaration for ECS to include it in derived system classes and be able to manipulate with the system during run invoke
class ECS;

/**
 * @class System
 * @brief Base class for ECS systems.
 *
 * The System class serves as the base class for systems in the ECS (Entity Component System) framework.
 * Systems in ECS are responsible for processing entities based on their signatures.
 * They define operations to run on entities that match their specific signature.
 */
class LANIAKEA_ECS_API System
{

public:

	System () = default;

    /**
     * @brief Virtual destructor for the System class.
     *
     * Virtual destructor to ensure proper cleanup of derived classes.
     */
	virtual ~System () = default;
    // Begin System interface

    /**
     * @brief Run the system for processing entities.
     * @param ecs The ECS (Entity Component System) instance used for processing.
     *
     * This pure virtual method is to be implemented by derived classes.
     * It defines the behavior of the system for processing entities that match the system's signature.
     *
     * @note The derived class must override this method to provide the implementation for processing entities.
     */
    virtual void Run ( ECS & ecs ) = 0;

    /**
     * @brief Add an entity to the system.
     * @param entity The entity to be added to the system.
     *
     * This method adds an entity to the system for processing.
     * It associates the entity with its corresponding handle in the system.
     */
	void AddEntity ( Entity & entity );

    /**
     * @brief Remove an entity from the system.
     * @param e The entity to be removed from the system.
     *
     * This method removes an entity from the system.
     * It disassociates the entity from its corresponding handle in the system.
     */
    void RemoveEntity ( Entity & entity );

    /**
     * @brief Set the signature for the system.
     * @param signature The new signature specifying the component types required by this system.
     *
     * This method sets the signature for the system, specifying the required component types.
     */
    void SetSignature ( const Signature & signature );

    /**
     * @brief Set the signature for the system.
     * @param signature The new signature specifying the component types required by this system.
     *
     * This method sets the signature for the system, specifying the required component types.
     */
    void SetSignature ( Signature && signature );

    /**
     * @brief Handle changes in the entity's signature.
     * @param entity The entity whose signature has changed.
     * @param signature The new signature of the entity.
     *
     * This method is called when the signature of an entity changes.
     * It compares the entity's new signature with the system's signature to decide whether to add or remove the entity from the system.
     * If the entity's signature matches the system's signature, the entity is added to the system for processing.
     * Otherwise, the entity is removed from the system.
     */
    void OnEntitySignatureChanged (Entity & entity, const Signature & signature );
    // End System interface


    // Begin System safe interface

    /**
     * @brief Safely add an entity to the system.
     * @param entity The entity to be added to the system.
     * @return True if the entity is added successfully, false if the entity is already in the system.
     *
     * This method safely adds an entity to the system for processing, avoiding duplicates.
     * It checks if the entity is already associated with the system and only adds it if it's not present.
     * Returns true if the entity is added successfully, false if the entity is already in the system.
     */
	bool AddEntityChecked ( Entity & entity );

    /**
     * @brief Safely remove an entity from the system.
     * @param entity The entity to be removed from the system.
     * @return True if the entity is removed successfully, false if the entity is not in the system.
     *
     * This method safely removes an entity from the system.
     * It checks if the entity is associated with the system and only removes it if it's present.
     * Returns true if the entity is removed successfully, false if the entity is not in the system.
     */
	bool RemoveEntityChecked ( Entity & entity );
    // End system safe interface

private:
    Signature m_Signature;  /**< The signature specifying the required component types for the system. */
    std::unordered_map<EntityHandle, ObjectHandle> m_EntitiesHandles;  /**< Mapping of entity handles to object handles in the system. */
protected:
    ObjectManager<EntityHandle> m_Entities;  /**< ObjectManager to handle entities associated with the system. */
};