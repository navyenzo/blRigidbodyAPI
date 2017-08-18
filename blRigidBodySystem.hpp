#ifndef BL_RIGIDBODYSYSTEM_HPP
#define BL_RIGIDBODYSYSTEM_HPP


//-------------------------------------------------------------------
// FILE:            blRigidBodySystem.hpp
// CLASS:           blRigidBodySystem
// BASE CLASS:      blRigidBody
//
// PURPOSE:         Based on blRigidBody, it adds a set of rigid
//                  bodies used to simulate a system of rigid
//                  bodies
//
// AUTHOR:          Vincenzo Barbato
//                  http://www.barbatolabs.com
//                  navyenzo@gmail.com
//
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
//
// DEPENDENCIES:    - std::set
//                  - blRigidBody and all its dependencies
//
// NOTES:
//
// DATE CREATED:    May/16/2011
// DATE UPDATED:
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Includes and libs needed for this file
//-------------------------------------------------------------------
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Enums used for this file and sub-files
//-------------------------------------------------------------------
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
class blRigidBodySystem : public blRigidBody<blDataType>
{
protected: // Protected typedefs

    typedef typename blRigidBody<blDataType>::blVectorType              blVectorType;

    typedef std::vector< blRigidBodySystem<blDataType> >                blRigidBodyContainerType;
    typedef std::vector< blConnection<blDataType> >                     blConnectionContainerType;

public: // Constructors and destructors

    // Default constructor
    blRigidBodySystem(const bool& shouldParentBodyBeSimulated = true,
                      const bool& shouldChildrenBodiesBeSimulated = true,
                      const blVectorType& additionalField = blVectorType(0,0,0),
                      const int& integrationMethod = BL_EULER,
                      const sf::Time& startingSimulationTime = sf::seconds(0));

    // Copy constructor
    blRigidBodySystem(const blRigidBodySystem<blDataType>& rigidBodySystem);

    // Destructor
    ~blRigidBodySystem();

public: // Public functions

    // Simulation
    // functions

    void                                                simulate();

    virtual void                                        simulateWithTime(const sf::Time& deltaTime,
                                                                         const sf::Time& totalTime);

    // Functions used to
    // set/get the managers
    // holding the rigid
    // bodies

    void                                                setRigidBodyManager(const blRigidBodyContainerType& rigidBodyManager);

    blRigidBodyContainerType&                           getRigidBodyManager();
    const blRigidBodyContainerType&                     getRigidBodyManager()const;

    // Functions used to
    // set/get the managers
    // holding the rigid
    // body connections

    void                                                setConnectionsManager(const blConnectionContainerType& connectionsManager);
    blConnectionContainerType&                          getConnectionsManager();
    const blConnectionContainerType&                    getConnectionsManager()const;

    // Functions used to
    // set/get the total
    // simulation time

    const sf::Time&                                     getTotalSimulationTime()const;
    void                                                setTotalSimulationTime(const sf::Time& totalSimulationTime);

    // Function used to
    // resolve motion
    // limits

    virtual void                                        resolveMotionLimits();
    virtual void                                        resolveAngularMotionLimits();

    // Functions used to
    // get additional
    // parameters needed
    // in the simulation

    const bool&                                         getShouldParentBodyBeSimulated()const;
    const bool&                                         getShouldChildrenBodiesBeSimulated()const;
    const blVectorType&                                 getAdditionalField()const;
    const int&                                          getIntegrationMethod()const;

    void                                                setShouldParentBodyBeSimulated(const bool& shouldParentBodyBeSimulated);
    void                                                setShouldChildrenBodiesBeSimulated(const bool& shouldChildrenBodiesBeSimulated);
    void                                                setAdditionalField(const blVectorType& additionalField);
    void                                                setIntegrationMethod(const int& integrationMethod);

protected: // Protected variables

    // additional field
    // added to the total
    // rigid body acceleration.
    // For ex. Gravitational
    // field

    blVectorType                                        m_additionalField;

    // Manager holding
    // our rigid bodies

    blRigidBodyContainerType                            m_rigidBodyManager;

    // Manager holding
    // our rigid body
    // connections

    blConnectionContainerType                           m_connectionsManager;

private: // Private variables

    // Clock and time
    // used for
    // simulations

    sf::Clock                                           m_simulationClock;
    sf::Time                                            m_totalSimulationTime;

    // additional parameters
    // needed when simulating

    bool                                                m_shouldParentBodyBeSimulated;
    bool                                                m_shouldChildrenBodiesBeSimulated;
    blVectorType                                        m_m_additionalField;
    int                                                 m_integrationMethod;
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blRigidBodySystem<blDataType>::blRigidBodySystem(const bool& shouldParentBodyBeSimulated,
                                                        const bool& shouldChildrenBodiesBeSimulated,
                                                        const blVectorType& additionalField,
                                                        const int& integrationMethod,
                                                        const sf::Time& startingSimulationTime)
                                                        : blRigidBody<blDataType>()
{
    setShouldParentBodyBeSimulated(shouldParentBodyBeSimulated);
    setShouldChildrenBodiesBeSimulated(shouldChildrenBodiesBeSimulated);
    setAdditionalField(additionalField);
    setIntegrationMethod(integrationMethod);

    setTotalSimulationTime(startingSimulationTime);
    m_simulationClock.restart();
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blRigidBodySystem<blDataType>::blRigidBodySystem(const blRigidBodySystem<blDataType>& rigidBodySystem)
                                                        : blRigidBody<blDataType>(rigidBodySystem)
{
    // Copy the rigid
    // bodies manager

    setRigidBodyManager(rigidBodySystem.getRigidBodyManager());

    // Copy the
    // connections
    // manager

    setConnectionsManager(rigidBodySystem.getConnectionsManager());

    // Copy the additional
    // parameters needed
    // in the simulation

    setShouldParentBodyBeSimulated(rigidBodySystem.getShouldParentBodyBeSimulated());
    setShouldChildrenBodiesBeSimulated(rigidBodySystem.getShouldChildrenBodiesBeSimulated());
    setAdditionalField(rigidBodySystem.getAdditionalField());
    setIntegrationMethod(rigidBodySystem.getIntegrationMethod());

    // Copy the total
    // simulation time

    setTotalSimulationTime(rigidBodySystem.getTotalSimulationTime());
    m_simulationClock.restart();
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blRigidBodySystem<blDataType>::~blRigidBodySystem()
{
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRigidBodySystem<blDataType>::setTotalSimulationTime(const sf::Time& totalSimulationTime)
{
    m_totalSimulationTime = totalSimulationTime;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const sf::Time& blRigidBodySystem<blDataType>::getTotalSimulationTime()const
{
    return m_totalSimulationTime;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const bool& blRigidBodySystem<blDataType>::getShouldParentBodyBeSimulated()const
{
    return m_shouldParentBodyBeSimulated;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const bool& blRigidBodySystem<blDataType>::getShouldChildrenBodiesBeSimulated()const
{
    return m_shouldChildrenBodiesBeSimulated;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const typename blRigidBodySystem<blDataType>::blVectorType& blRigidBodySystem<blDataType>::getAdditionalField()const
{
    return m_additionalField;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const int& blRigidBodySystem<blDataType>::getIntegrationMethod()const
{
    return m_integrationMethod;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRigidBodySystem<blDataType>::setShouldParentBodyBeSimulated(const bool& shouldParentBodyBeSimulated)
{
    m_shouldParentBodyBeSimulated = shouldParentBodyBeSimulated;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRigidBodySystem<blDataType>::setShouldChildrenBodiesBeSimulated(const bool& shouldChildrenBodiesBeSimulated)
{
    m_shouldChildrenBodiesBeSimulated = shouldChildrenBodiesBeSimulated;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRigidBodySystem<blDataType>::setAdditionalField(const blVectorType& additionalField)
{
    m_additionalField = additionalField;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRigidBodySystem<blDataType>::setIntegrationMethod(const int& integrationMethod)
{
    m_integrationMethod = integrationMethod;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline typename blRigidBodySystem<blDataType>::blRigidBodyContainerType& blRigidBodySystem<blDataType>::getRigidBodyManager()
{
    return m_rigidBodyManager;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const typename blRigidBodySystem<blDataType>::blRigidBodyContainerType& blRigidBodySystem<blDataType>::getRigidBodyManager()const
{
    return m_rigidBodyManager;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline typename blRigidBodySystem<blDataType>::blConnectionContainerType& blRigidBodySystem<blDataType>::getConnectionsManager()
{
    return m_connectionsManager;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const typename blRigidBodySystem<blDataType>::blConnectionContainerType& blRigidBodySystem<blDataType>::getConnectionsManager()const
{
    return m_connectionsManager;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRigidBodySystem<blDataType>::setRigidBodyManager(const blRigidBodyContainerType& rigidBodyManager)
{
    m_rigidBodyManager = rigidBodyManager;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRigidBodySystem<blDataType>::setConnectionsManager(const blConnectionContainerType& connectionsManager)
{
    m_connectionsManager = connectionsManager;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRigidBodySystem<blDataType>::simulate()
{
    m_totalSimulationTime += m_simulationClock.getElapsedTime();

    simulateWithTime(m_simulationClock.getElapsedTime(),
                     m_totalSimulationTime);

    m_simulationClock.restart();
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRigidBodySystem<blDataType>::simulateWithTime(const sf::Time& deltaTime,
                                                            const sf::Time& totalTime)
{
    // Go through all the
    // connections and
    // calculate/apply all
    // the forces/torques
    // to the rigid bodies
    // due to the connections

    for(auto myConnections = m_connectionsManager.begin();
        myConnections != m_connectionsManager.end();
        ++myConnections)
    {
        if(*myConnections)
        {
            (*myConnections)->calculateAndApplyForcesAndTorques();
        }
    }

    // Call the base function
    // if the parent object is
    // to be simulated

    if(m_shouldParentBodyBeSimulated)
        this->simulateRigidBody(deltaTime,
                                totalTime,
                                m_additionalField,
                                m_integrationMethod);

    // Call the childrens'
    // simulation functions

    if(m_shouldChildrenBodiesBeSimulated)
    {
        // simulate all the rigid
        // bodies managed by this
        // rigid body system

        for(auto myRigidBodies = m_rigidBodyManager.begin();
            myRigidBodies != m_rigidBodyManager.end();
            ++myRigidBodies)
        {

            if(*myRigidBodies)
            {
                (*myRigidBodies)->simulateWithTime(deltaTime,
                                                   totalTime);
            }
        }
    }
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRigidBodySystem<blDataType>::resolveMotionLimits()
{
    // Loop through the
    // sub-rigid bodies
    // and resolve their
    // individual
    // motion limits

    for(auto myRigidBodies = m_rigidBodyManager.begin();
        myRigidBodies != m_rigidBodyManager.end();
        ++myRigidBodies)
    {

        if(*myRigidBodies)
        {
            (*myRigidBodies)->resolveMotionLimits();
        }
    }

    // Now we resolve this rigid
    // body's motion limits

    blRigidBody<blDataType>::resolveMotionLimits();
}

//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRigidBodySystem<blDataType>::resolveAngularMotionLimits()
{
    // Loop through the
    // sub-rigid bodies
    // and resolve their
    // individual
    // motion limits

    for(auto myRigidBodies = m_rigidBodyManager.begin();
        myRigidBodies != m_rigidBodyManager.end();
        ++myRigidBodies)
    {

        if(*myRigidBodies)
        {
            (*myRigidBodies)->resolveAngularMotionLimits();
        }
    }

    // Now we resolve this rigid
    // body's motion limits

    blRigidBody<blDataType>::resolveAngularMotionLimits();
}
//-------------------------------------------------------------------


#endif // BL_RIGIDBODYSYSTEM_HPP
