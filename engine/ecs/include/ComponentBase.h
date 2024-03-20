#pragma once

#include "Types.h"

/**
 * @class ComponentBase
 * @brief The base class for components attached to entities.
 *
 * This class serves as the foundation for all components that can be attached to entities in the system.
 * It contains functionality to store the owner entity handle and retrieve it when needed.
 */
class ComponentBase
{

public:
    /**
     * @brief Constructor for ComponentBase.
     * @param owner The handle of the entity that owns this component.
     */
	explicit ComponentBase ( EntityHandle owner );

    /**
     * @brief Get the owner entity handle.
     * @return The handle of the entity that owns this component.
     */
	EntityHandle GetOwner () const;

private:
	EntityHandle m_Owner; /**< The handle of the entity that owns this component. */
};
