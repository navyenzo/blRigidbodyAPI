#ifndef BL_RIGIDBODY_HPP
#define BL_RIGIDBODY_HPP


//-------------------------------------------------------------------
// FILE:            blRigidBody.hpp
// CLASS:           blRigidBody
// BASE CLASS:      - blIDSystem
//                  - blPosition
//                  - blVelocity
//                  - blOrientation
//                  - blAngularVelocity
//                  - blSize
//                  - blInertia
//                  - blDamping
//                  - blRestitution
//
// PURPOSE:         Based on classes blIDSystem,blPosition,blVelocity,
//                  blOrientation,blAngularVelocity and blInertia,
//                  blDamping, blRestitution, it combines all these
//                  properties into an object to represent a rigid
//                  body and its dynamics
//
// AUTHOR:          Vincenzo Barbato
//                  http://www.barbatolabs.com
//                  navyenzo@gmail.com
//
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
//
// DEPENDENCIES:
//
// NOTES:
//
// DATE CREATED:    Nov/08/2010
// DATE UPDATED:
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Includes and libs needed for this file
//-------------------------------------------------------------------
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Enums needed for this file
//-------------------------------------------------------------------

    // Enum used for choosing integration methods
    enum {BL_EULER = 0,
          BL_RK4 = 1,
          BL_VERLET = 2};

//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
class blRigidBody : public blPosition<blDataType>,
                    public blVelocity<blDataType>,
                    public blOrientation<blDataType>,
                    public blAngularVelocity<blDataType>,
                    public blSize<blDataType>,
                    public blInertia<blDataType>,
                    public blDamping<blDataType>,
                    public blRestitution<blDataType>
{
protected: // Protected typedefs

    typedef typename blOrientation<blDataType>::blVectorType        blVectorType;
    typedef typename blOrientation<blDataType>::blQuaternionType    blQuaternionType;
    typedef typename blInertia<blDataType>::blMatrixType            blMatrixType;

public: // Constructors and destructors

    // Default constructor

    blRigidBody();

    // Copy constructor

    blRigidBody(const blRigidBody<blDataType>& rigidBody);

    // Destructor

    ~blRigidBody()
    {
    }

public: // Public functions

    // Function used to
    // add a simple force
    // acting on the center
    // of mass

    void                                                addForce(const blVectorType& force);

    // Function used to
    // add a simple torque

    void                                                addTorque(const blVectorType& torque);

    // Function used to
    // add a force acting
    // at some arbitrary point

    void                                                addForceAndTorque(const blVectorType& force,
                                                                          const blVectorType& forcePosition);

    // Function used to
    // simulate this
    // rigid body

    virtual void                                        simulateRigidBody(const sf::Time& timeStep,
                                                                          const sf::Time& totalTime,
                                                                          const blVectorType& additionalField,
                                                                          const int& integrationMethod);

    // Functions used to
    // resolve motion
    // and angular motion
    // limits

    virtual void                                        resolveMotionLimits();
    virtual void                                        resolveAngularMotionLimits();

    // Function used to
    // transform the
    // connection positions
    // from their body
    // coordinates to global
    // coordinates

    void                                                fromBodyToSystemCoordinates(blVectorType& vectorToTransform);

protected: // Protected functions

    // Eurler integration
    // methods

    virtual void                                        calculateNewStateUsingEuler(const sf::Time& timeStep,
                                                                                    const sf::Time& totalTime,
                                                                                    const blVectorType& accelerationField);

    // Runga-Kutta 4th
    // order method

    virtual void                                        calculateNewStateUsingRK4(const sf::Time& timeStep,
                                                                                  const sf::Time& totalTime,
                                                                                  const blVectorType& accelerationField);

protected: // Protected temp variables

    // total force/torque
    // variables used
    // to interface with
    // the rigid body

    blVectorType                                        m_totalForce;
    blVectorType                                        m_totalTorque;
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blRigidBody<blDataType>::blRigidBody() : blPosition<blDataType>(),
                                                blVelocity<blDataType>(),
                                                blOrientation<blDataType>(),
                                                blAngularVelocity<blDataType>(),
                                                blInertia<blDataType>(),
                                                blDamping<blDataType>(),
                                                blRestitution<blDataType>()
{
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blRigidBody<blDataType>::blRigidBody(const blRigidBody& rigidBody)
                                            : blPosition<blDataType>(rigidBody),
                                              blVelocity<blDataType>(rigidBody),
                                              blOrientation<blDataType>(rigidBody),
                                              blAngularVelocity<blDataType>(rigidBody),
                                              blSize<blDataType>(rigidBody),
                                              blInertia<blDataType>(rigidBody),
                                              blDamping<blDataType>(rigidBody),
                                              blRestitution<blDataType>(rigidBody)
{
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRigidBody<blDataType>::addForce(const blVectorType& force)
{
    m_totalForce += force;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRigidBody<blDataType>::addTorque(const blVectorType& torque)
{
    m_totalTorque += torque;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRigidBody<blDataType>::addForceAndTorque(const blVectorType& force,
                                                       const blVectorType& forcePosition)
{
    m_totalForce += force;
    m_totalTorque += crossProduct((forcePosition - this->getPosition()),force);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRigidBody<blDataType>::simulateRigidBody(const sf::Time& timeStep,
                                                       const sf::Time& totalTime,
                                                       const blVectorType& accelerationField,
                                                       const int& integrationMethod)
{
    // Before we integrate
    // the rigid body's
    // state, we add damping
    // losses into the total
    // body forces

    m_totalForce += this->calculateDamping(this->getVelocity());
    m_totalTorque += this->calculateAngularDamping(this->getAngularVelocity());

    // Depending on the
    // integration method
    // we call the appropriate
    // function to calculate
    // the new state of the
    // rigid body

    switch(integrationMethod)
    {
    case BL_EULER:
        calculateNewStateUsingEuler(timeStep,totalTime,accelerationField);
        break;

    case BL_RK4:
        calculateNewStateUsingRK4(timeStep,totalTime,accelerationField);
        break;

    default:
        calculateNewStateUsingEuler(timeStep,totalTime,accelerationField);
        break;
    }

    // Before moving on
    // we need to check
    // the motion limits

    resolveMotionLimits();
    resolveAngularMotionLimits();

    // Reset the total
    // force acting on
    // rigid body

    m_totalForce.x = 0;
    m_totalForce.y = 0;
    m_totalForce.z = 0;

    // Reset the total
    // torque acting on
    // rigid body

    m_totalTorque.x = 0;
    m_totalTorque.y = 0;
    m_totalTorque.z = 0;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRigidBody<blDataType>::calculateNewStateUsingEuler(const sf::Time& timeStep,
                                                                 const sf::Time& totalTime,
                                                                 const blVectorType& accelerationField)
{
    // Step 1:  Integrate the
    //          position

    this->translate(this->getVelocity() * timeStep.asSeconds());

    // Step 2:  Integrate the
    //          velocity

    this->changeVelocity((m_totalForce/this->getMass() + accelerationField) * timeStep.asSeconds());

    // Step 3:  Integrate the
    //          angular position

        // Form a quaternion
        // out of the angular
        // velocity

        blDataType theta = this->getAngularVelocity().getMagnitude() * timeStep.asSeconds();

        blQuaternionType angVelQtn(std::cos(theta/2.0),
                                   this->getAngularVelocity() * std::sin(theta/2.0));

        this->rotate(angVelQtn);

    // Step 4:  Integrate the
    //          angular velocity

    this->changeAngularVelocity(this->getInertiaInverse() *
                                (m_totalTorque - crossProduct(this->getAngularVelocity(),this->getInertia() * this->getAngularVelocity())) *
                                timeStep.asSeconds());
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRigidBody<blDataType>::calculateNewStateUsingRK4(const sf::Time& timeStep,
                                                               const sf::Time& totalTime,
                                                               const blVectorType& accelerationField)
{
    // calculate the
    // acceleration
    // using F = ma

    blVectorType acceleration = m_totalForce/this->getMass() + accelerationField;

    // Store the current
    // position into the
    // old position
    // m_OldPosition = m_position;

    // Integrate using a
    // fourth order
    // Runga-Kutta method
    // for a system of
    // equations
    //
    // Let x1 = position
    // Let x2 = velocity
    //
    // dx1/dt = x2
    // dx2/dt = a
    //
    // k11 = f1(ti,x1i,x2i)								= m_velocity
    // k12 = f2(ti,x1i,x2i)								= acceleration
    // k21 = f1(ti,x1i + 0.5*k11*dt,x2i + 0.5*k12*dt)	= m_velocity + 0.5*k12*timeStep
    // k22 = f2(ti,x1i + 0.5*k11*dt,x2i + 0.5*k12*dt)	= acceleration
    // k31 = f1(ti,x1i + 0.5*k21*dt,x2i + 0.5*k22*dt)	= m_velocity + 0.5*k22*timeStep
    // k32 = f2(ti,x1i + 0.5*k21*dt,x2i + 0.5*k22*dt)	= acceleration
    // k41 = f1(ti,x1i + k31*dt,x2i + k32*dt)			= m_velocity + k32*timeStep
    // k42 = f2(ti,x1i + k31*dt,x2i + k32*dt)			= acceleration
    //
    // m_position = m_position + (k11 + 2*(k21 + k31) + k41)*dt/6
    // m_velocity = m_velocity + (k12 + 2*(k22 + k32) + k42)*dt/6
    //
    // Let's try to make
    // these more efficient
    // by directly substituting
    // the coefficients in
    // and then simplifying:

    blVectorType k11,k12,k21,k22,k31,k32,k41,k42;

    k11 = this->getVelocity();
    k12 = acceleration;
    k21 = this->getVelocity() + blDataType(0.5)*k12*timeStep.asSeconds();
    k22 = acceleration;
    k31 = this->getVelocity() + blDataType(0.5)*k22*timeStep.asSeconds();
    k32 = acceleration;
    k41 = this->getVelocity() + k32*timeStep.asSeconds();
    k42 = acceleration;

    this->translate((k11 + blDataType(2)*(k21 + k31) + k41) * (blDataType(timeStep.asSeconds())/blDataType(6)));
    this->changeVelocity((k12 + blDataType(2)*(k22 + k32) + k42) * (blDataType(timeStep.asSeconds())/blDataType(6)));
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRigidBody<blDataType>::fromBodyToSystemCoordinates(blVectorType& vectorToTransform)
{
    // Step 1:  Account for the
    //          size of this
    //          rigid body by
    //          scaling the vector

    vectorToTransform.x *= this->m_Size.x;
    vectorToTransform.y *= this->m_Size.y;
    vectorToTransform.z *= this->m_Size.z;

    // Step 2:  Account for the
    //          rotation of this
    //          rigid body by
    //          rotating the vector

    vectorToTransform = vectorToTransform.getMagnitude() *
                        (this->m_RotQtn *
                         blQuaternionType(0,vectorToTransform) *
                         this->m_RotQtn.getConjugate()).m_xyz;

    // Step 3:  Account for the
    //          position of this
    //          rigid body by
    //          translating the
    //          vector

    vectorToTransform += this->getPosition();
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRigidBody<blDataType>::resolveMotionLimits()
{
    // We check the
    // translation
    // limits

    // calculate the
    // total movement
    // from its starting
    // position

    blVectorType totalMovement = this->calculateMovement();

    // Check the
    // x limits

    if(this->getIsMotionLimited().x)
    {
        if(totalMovement.x < this->getMotionLowerLimits().x)
        {
            this->translate(this->getMotionLowerLimits().x - totalMovement.x,0,0);
            this->changeVelocity(-(1.0 + this->getRestitutionCoefficients().x) * this->getVelocity().x,0,0);
        }
        else if(totalMovement.x > this->getMotionUpperLimits().x)
        {
            this->translate(this->getMotionUpperLimits().x - totalMovement.x,0,0);
            this->changeVelocity(-(1.0 + this->getRestitutionCoefficients().x) * this->getVelocity().x,0,0);
        }
    }

    // Check the
    // y limits

    if(this->getIsMotionLimited().y)
    {
        if(totalMovement.y < this->getMotionLowerLimits().y)
        {
            this->translate(0,this->getMotionLowerLimits().y - totalMovement.y,0);
            this->changeVelocity(0,-(1.0 + this->getRestitutionCoefficients().y) * this->getVelocity().y,0);
        }
        else if(totalMovement.y > this->getMotionUpperLimits().y)
        {
            this->translate(0,this->getMotionUpperLimits().y - totalMovement.y,0);
            this->changeVelocity(0,-(1.0 + this->getRestitutionCoefficients().y) * this->getVelocity().y,0);
        }
    }

    // Check the
    // x limits

    if(this->getIsMotionLimited().z)
    {
        if(totalMovement.z < this->getMotionLowerLimits().z)
        {
            this->translate(0,0,this->getMotionLowerLimits().z - totalMovement.z);
            this->changeVelocity(0,0,-(1.0 + this->getRestitutionCoefficients().z) * this->getVelocity().z);
        }
        else if(totalMovement.z > this->getMotionUpperLimits().z)
        {
            this->translate(0,0,this->getMotionUpperLimits().z - totalMovement.z);
            this->changeVelocity(0,0,-(1.0 + this->getRestitutionCoefficients().z) * this->getVelocity().z);
        }
    }
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRigidBody<blDataType>::resolveAngularMotionLimits()
{
    if(this->getIsAngularMotionLimited().x ||
       this->getIsAngularMotionLimited().y ||
       this->getIsAngularMotionLimited().z)
    {
        bool shouldWeResetRotation = false;
        blVectorType totalEulerAngles = this->getTotalEulerAngles();
        blVectorType angularVelocity = this->getAngularVelocity();

        // Check the
        // x rotation

        if(this->getIsAngularMotionLimited().x)
        {
            if(totalEulerAngles.x < this->getAngularMotionLowerLimits().x)
            {
                totalEulerAngles.x = this->getAngularMotionLowerLimits().x;
                angularVelocity.x = -angularVelocity.x * this->getAngularRestitutionCoefficients().x;
                shouldWeResetRotation = true;
            }
            else if(totalEulerAngles.x > this->getAngularMotionUpperLimits().x)
            {
                totalEulerAngles.x = this->getAngularMotionUpperLimits().x;
                angularVelocity.x = -angularVelocity.x * this->getAngularRestitutionCoefficients().x;
                shouldWeResetRotation = true;
            }
        }

        // Check the
        // y rotation

        if(this->getIsAngularMotionLimited().y)
        {
            if(totalEulerAngles.y < this->getAngularMotionLowerLimits().y)
            {
                totalEulerAngles.y = this->getAngularMotionLowerLimits().y;
                angularVelocity.y = -angularVelocity.y * this->getAngularRestitutionCoefficients().y;
                shouldWeResetRotation = true;
            }
            else if(totalEulerAngles.y > this->getAngularMotionUpperLimits().y)
            {
                totalEulerAngles.y = this->getAngularMotionUpperLimits().y;
                angularVelocity.y = -angularVelocity.y * this->getAngularRestitutionCoefficients().y;
                shouldWeResetRotation = true;
            }
        }

        // Check the
        // z rotation

        if(this->getIsAngularMotionLimited().z)
        {
            if(totalEulerAngles.z < this->getAngularMotionLowerLimits().z)
            {
                totalEulerAngles.z = this->getAngularMotionLowerLimits().z;
                angularVelocity.z = -angularVelocity.z * this->getAngularRestitutionCoefficients().z;
                shouldWeResetRotation = true;
            }
            else if(totalEulerAngles.z > this->getAngularMotionUpperLimits().z)
            {
                totalEulerAngles.z = this->getAngularMotionUpperLimits().z;
                angularVelocity.z = -angularVelocity.z * this->getAngularRestitutionCoefficients().z;
            }
        }

        // NOTE:    We do not
        //          want to store
        //          the current
        //          rotation as the
        //          "earlier" rotation,
        //          just because
        //          then the "earlier"
        //          rotation would
        //          be out of range

        // set the euler
        // angles as the
        // new rotation
        // quaternion

        if(shouldWeResetRotation)
        {
            this->setAngularVelocity(angularVelocity);
            this->adjustOrientation(totalEulerAngles);
        }
    }
}
//-------------------------------------------------------------------


#endif // BL_RIGIDBODY_HPP
