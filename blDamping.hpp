#ifndef BL_DAMPING_HPP
#define BL_DAMPING_HPP


//-------------------------------------------------------------------
// FILE:            blDamping.hpp
// CLASS:           blDamping
// BASE CLASS:      None
//
// PURPOSE:         A base class to add damping
//                  energy losses to an object
//
// AUTHOR:          Vincenzo Barbato
//                  http://www.barbatolabs.com
//                  navyenzo@gmail.com
//
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
//
// DEPENDENCIES:    blMathAPI::blVector3d -- From the blMathAPI used to
//                                           calculate damping forces
//                                           depending on velocity and
//                                           angular velocity
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
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
class blDamping
{
protected: // Protected typedefs

    typedef blMathAPI::blVector3d<blDataType>                   blVectorType;

public: // Constructors and destructors

    // Default constructor

    blDamping(const blDataType& dampingCoefficient = 0,
              const blDataType& angularDampingCoefficient = 0);

    // Copy constructor

    blDamping(const blDamping<blDataType>& damping);

    // Destructor

    ~blDamping()
    {
    }

public: // Public function

    // Functions used to
    //  set/get the damping
    // coefficient

    virtual void                                                setDampingCoefficient(const blDataType& dampingCoefficient);
    const blDataType&                                           getDampingCoefficient()const;

    // Functions used to
    //  set/get the angular
    // damping coefficient

    virtual void                                                setAngularDampingCoefficient(const blDataType& angularDampingCoefficient);
    const blDataType&                                           getAngularDampingCoefficient()const;

    // Function used to
    // calculate the
    // damping force/torque

    virtual blVectorType                                        calculateDamping(const blVectorType& velocity);
    virtual blVectorType                                        calculateAngularDamping(const blVectorType& angularVelocity);

private: // Private variables

    // The damping
    // coefficient

    blDataType                                                  m_dampingCoefficient;
    blDataType                                                  m_angularDampingCoefficient;
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blDamping<blDataType>::blDamping(const blDataType& dampingCoefficient,
                                        const blDataType& angularDampingCoefficient)
{
    this->setDampingCoefficient(dampingCoefficient);
    this->setAngularDampingCoefficient(angularDampingCoefficient);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blDamping<blDataType>::blDamping(const blDamping<blDataType>& damping)
{
    this->setDampingCoefficient(damping.getDampingCoefficient());
    this->setAngularDampingCoefficient(damping.getAngularDampingCoefficient());
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blDamping<blDataType>:: setDampingCoefficient(const blDataType& dampingCoefficient)
{
    m_dampingCoefficient = dampingCoefficient;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType& blDamping<blDataType>::getDampingCoefficient()const
{
    return m_dampingCoefficient;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blDamping<blDataType>:: setAngularDampingCoefficient(const blDataType& angularDampingCoefficient)
{
    m_angularDampingCoefficient = angularDampingCoefficient;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType& blDamping<blDataType>::getAngularDampingCoefficient()const
{
    return m_angularDampingCoefficient;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline typename blDamping<blDataType>::blVectorType blDamping<blDataType>::calculateDamping(const blVectorType& velocity)
{
    return -m_dampingCoefficient*velocity;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline typename blDamping<blDataType>::blVectorType blDamping<blDataType>::calculateAngularDamping(const blVectorType& angularVelocity)
{
    return -m_angularDampingCoefficient*angularVelocity;
}
//-------------------------------------------------------------------


#endif // BL_DAMPING_HPP
