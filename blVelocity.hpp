#ifndef BL_VELOCITY_HPP
#define BL_VELOCITY_HPP


//-------------------------------------------------------------------
// FILE:            blVelocity.hpp
// CLASS:           blVelocity
// BASE CLASS:      None
//
// PURPOSE:         A base class to add
//                  velocity to an object
//
// AUTHOR:          Vincenzo Barbato
//                  http://www.barbatolabs.com
//                  navyenzo@gmail.com
//
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
//
// DEPENDENCIES:    blMathAPI::blVector3d -- From the blMathAPI used to
//                                           represent the velocity
//
// NOTES:
//
// DATE CREATED:    Nov/08/2010
//
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
class blVelocity
{
protected: // Protected typedefs

    typedef blMathAPI::blVector3d<blDataType>       blVectorType;

public: // Constructors and destructors

    // Default constructor

    blVelocity(const blDataType& xVel = 0,
               const blDataType& yVel = 0,
               const blDataType& zVel = 0);

    // Constructor from
    // a vector

    blVelocity(const blVectorType& velocity);

    // Copy constructor
    // (from a different
    // type velocity)

    template<typename blDataType2>
    blVelocity(const blVelocity<blDataType2>& velocity);

    // Destructor

    ~blVelocity()
    {
    }

public: // Public functions

    // Functions used to
    // get the velocity

    const blVectorType&                                 getVelocity()const;

    // Function used to
    // set the velocity
    // using a vector

    void                                                setVelocity(const blVectorType& velocity);

    // Funtion used to
    // set the velocity
    // using three values

    void                                                setVelocity(const blDataType& xPos,
                                                                    const blDataType& yPos,
                                                                    const blDataType& zPos);

    // Functions used to
    // change the current
    // velocity

    void                                                changeVelocity(const blVectorType& velocityChange);
    void                                                changeVelocity(const blDataType& xChange,
                                                                       const blDataType& yChange,
                                                                       const blDataType& zChange);

private: // Private variables

    // The velocity
    // vector

    blVectorType                                        m_velocity;
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blVelocity<blDataType>::blVelocity(const blDataType& xPos,
                                          const blDataType& yPos,
                                          const blDataType& zPos)
{
    m_velocity.x = xPos;
    m_velocity.y = yPos;
    m_velocity.z = zPos;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blVelocity<blDataType>::blVelocity(const blVectorType& velocity)
{
    m_velocity = velocity;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<typename blDataType2>
inline blVelocity<blDataType>::blVelocity(const blVelocity<blDataType2>& velocity)
{
    m_velocity = velocity.getVelocity();
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const typename blVelocity<blDataType>::blVectorType& blVelocity<blDataType>::getVelocity()const
{
    return m_velocity;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blVelocity<blDataType>::setVelocity(const blVectorType& velocity)
{
    m_velocity = velocity;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blVelocity<blDataType>::setVelocity(const blDataType& xPos,
                                                const blDataType& yPos,
                                                const blDataType& zPos)
{
    m_velocity.x = xPos;
    m_velocity.y = yPos;
    m_velocity.z = zPos;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blVelocity<blDataType>::changeVelocity(const blDataType& xChange,
                                                   const blDataType& yChange,
                                                   const blDataType& zChange)
{
    m_velocity.x += xChange;
    m_velocity.y += yChange;
    m_velocity.z += zChange;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blVelocity<blDataType>::changeVelocity(const blVectorType& velocityChange)
{
    m_velocity += velocityChange;
}
//-------------------------------------------------------------------



#endif // BL_VELOCITY_HPP
