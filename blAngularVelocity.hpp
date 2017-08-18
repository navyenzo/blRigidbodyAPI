#ifndef BL_ANGULARVELOCITY_HPP
#define BL_ANGULARVELOCITY_HPP


//-------------------------------------------------------------------
// FILE:            blAngularVelocity.hpp
// CLASS:           blAngularVelocity
// BASE CLASS:      None
//
// PURPOSE:         A base class to add angular velocity to an object
//
// AUTHOR:          Vincenzo Barbato
//                  http://www.barbatolabs.com
//                  navyenzo@gmail.com
//
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
//
// DEPENDENCIES:    blMathAPI::blVector3d -- From the blMathAPI used to
//                                           represent the angular velocity
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
class blAngularVelocity
{
protected: // Protected typedefs

    typedef blMathAPI::blVector3d<blDataType>           blVectorType;

public: // Constructors and destructors

    // Default constructor

    blAngularVelocity(const blDataType& xVel = 0,
                      const blDataType& yVel = 0,
                      const blDataType& zVel = 0);

    // Constructor from
    // a vector

    blAngularVelocity(const blVectorType& angularVelocity);

    // Copy constructor
    // (from a different
    // type angularVelocity)

    template<typename blDataType2>
    blAngularVelocity(const blAngularVelocity<blDataType2>& angularVelocity);

    // Destructor

    ~blAngularVelocity()
    {
    }

public: // Public functions

    // Functions used to
    // set/get the angular
    // velocity

    const blVectorType&                                 getAngularVelocity()const;
    void                                                setAngularVelocity(const blVectorType& angularVelocity);
    void                                                setAngularVelocity(const blDataType& xPos,
                                                                           const blDataType& yPos,
                                                                           const blDataType& zPos);

    // Functions used to
    // change the current
    // angular velocity

    void                                                changeAngularVelocity(const blVectorType& angularVelocityChange);
    void                                                changeAngularVelocity(const blDataType& xChange,
                                                                              const blDataType& yChange,
                                                                              const blDataType& zChange);

private: // Private variables

    // The angular
    // velocity vector

    blVectorType                                        m_angularVelocity;
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blAngularVelocity<blDataType>::blAngularVelocity(const blDataType& xPos,
                                                        const blDataType& yPos,
                                                        const blDataType& zPos)
{
    setAngularVelocity(xPos,yPos,zPos);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blAngularVelocity<blDataType>::blAngularVelocity(const blVectorType& angularVelocity)
{
    setAngularVelocity(angularVelocity);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<typename blDataType2>
inline blAngularVelocity<blDataType>::blAngularVelocity(const blAngularVelocity<blDataType2>& angularVelocity)
{
    setAngularVelocity(angularVelocity.getAngularVelocity());
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const typename blAngularVelocity<blDataType>::blVectorType& blAngularVelocity<blDataType>::getAngularVelocity()const
{
    return m_angularVelocity;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blAngularVelocity<blDataType>::setAngularVelocity(const blVectorType& angularVelocity)
{
    m_angularVelocity = angularVelocity;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blAngularVelocity<blDataType>::setAngularVelocity(const blDataType& xPos,
                                                              const blDataType& yPos,
                                                              const blDataType& zPos)
{
    m_angularVelocity.x() = xPos;
    m_angularVelocity.y() = yPos;
    m_angularVelocity.z() = zPos;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blAngularVelocity<blDataType>::changeAngularVelocity(const blDataType& xChange,
                                                                 const blDataType& yChange,
                                                                 const blDataType& zChange)
{
    m_angularVelocity.x() += xChange;
    m_angularVelocity.y() += yChange;
    m_angularVelocity.z() += zChange;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blAngularVelocity<blDataType>::changeAngularVelocity(const blVectorType& angularVelocityChange)
{
    m_angularVelocity += angularVelocityChange;
}
//-------------------------------------------------------------------


#endif // BL_ANGULARVELOCITY_HPP
