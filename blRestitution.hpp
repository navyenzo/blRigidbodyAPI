#ifndef BL_RESTITUTION_HPP
#define BL_RESTITUTION_HPP


//-------------------------------------------------------------------
// FILE:            blRestitution.hpp
// CLASS:           blRestitution
// BASE CLASS:      None
//
// PURPOSE:         A base class to add motion limits and
//                  restitution coefficients
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
// DATE CREATED:    Jul/18/2011
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
class blRestitution
{
protected: // Protected typedefs

    typedef blMathAPI::blVector3d<blDataType>               blVectorType;
    typedef blMathAPI::blVector3d<bool>                     blVectorBool;

public: // Constructors and destructors

    // Default constructor
    blRestitution(const blVectorType& restitutionCoefficients = blVectorType(1,1,1),
                  const blVectorType& angularRestitutionCoefficients = blVectorType(1,1,1),
                  const blVectorBool& isMotionLimited = blVectorBool(false,false,false),
                  const blVectorBool& isAngularMotionLimited = blVectorBool(false,false,false),
                  const blVectorType& motionLowerLimits = blVectorType(-1,-1,-1),
                  const blVectorType& motionUpperLimits = blVectorType(1,1,1),
                  const blVectorType& angularMotionLowerLimits = blVectorType(-blMathAPI::pi,-blMathAPI::pi,-blMathAPI::pi),
                  const blVectorType& angularMotionUpperLimits = blVectorType(blMathAPI::pi,blMathAPI::pi,blMathAPI::pi));

    // Copy constructor
    blRestitution(const blRestitution<blDataType>& restitution);

    // Destructor
    ~blRestitution()
    {
    }

public: // Public function

    // Functions used to
    // set/get the lower
    // and upper motion
    // limits

    void                                                    setMotionLimits(const blVectorType& motionLowerLimits,
                                                                            const blVectorType& motionUpperLimits);

    void                                                    setAngularMotionLimits(const blVectorType& angularMotionLowerLimits,
                                                                                   const blVectorType& angularMotionUpperLimits);

    const blVectorType&                                     getMotionLowerLimits()const;
    const blVectorType&                                     getMotionUpperLimits()const;
    const blVectorType&                                     getAngularMotionLowerLimits()const;
    const blVectorType&                                     getAngularMotionUpperLimits()const;

    // Functions used to
    // set/get the restitution
    // coefficient
    virtual void                                            setRestitutionCoefficients(const blDataType& xCoeff,
                                                                                       const blDataType& yCoeff,
                                                                                       const blDataType& zCoeff);

    virtual void                                            setRestitutionCoefficients(const blVectorType& restitutionCoefficient);

    const blVectorType&                                     getRestitutionCoefficients()const;

    // Functions used to
    // set/get the angular
    // restitution coefficient
    virtual void                                            setAngularRestitutionCoefficients(const blDataType& xCoeff,
                                                                                              const blDataType& yCoeff,
                                                                                              const blDataType& zCoeff);

    virtual void                                            setAngularRestitutionCoefficients(const blVectorType& AngularRestitutionCoefficient);

    const blVectorType&                                     getAngularRestitutionCoefficients()const;

    // Functions used to
    // set/get the booleans
    // determining whether
    // or not the motion
    // of this rigid body
    // is limited

    virtual void                                            setIsMotionLimited(const blVectorBool& isMotionLimited);

    virtual void                                            setIsMotionLimited(const bool& isXMotionLimited,
                                                                               const bool& isYMotionLimited,
                                                                               const bool& isZMotionLimited);

    const blVectorBool&                                     getIsMotionLimited()const;

    // Functions used to
    // set/get the booleans
    // determining whether
    // or not the angular
    // motion of this
    // rigid body is limited

    virtual void                                            setIsAngularMotionLimited(const blVectorBool& isAngularMotionLimited);

    virtual void                                            setIsAngularMotionLimited(const bool& isXAngularMotionLimited,
                                                                                      const bool& isYAngularMotionLimited,
                                                                                      const bool& isZAngularMotionLimited);

    const blVectorBool&                                     getIsAngularMotionLimited()const;

    // Functions used to
    // resolve the motion
    // limits
    virtual void                                            resolveMotionLimits();
    virtual void                                            resolveAngularMotionLimits();

private: // Private variables

    // The restitution
    // coefficient
    blVectorType                                            m_restitutionCoefficients;
    blVectorType                                            m_angularRestitutionCoefficients;

    // Booleans used to
    // determine if the
    // motion is limited
    blVectorBool                                            m_isMotionLimited;
    blVectorBool                                            m_isAngularMotionLimited;

    // The limits of
    // motion
    blVectorType                                            m_motionLowerLimits;
    blVectorType                                            m_motionUpperLimits;
    blVectorType                                            m_angularMotionLowerLimits;
    blVectorType                                            m_angularMotionUpperLimits;
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blRestitution<blDataType>::blRestitution(const blVectorType& restitutionCoefficients,
                                                const blVectorType& angularRestitutionCoefficients,
                                                const blVectorBool& isMotionLimited,
                                                const blVectorBool& isAngularMotionLimited,
                                                const blVectorType& motionLowerLimits,
                                                const blVectorType& motionUpperLimits,
                                                const blVectorType& angularMotionLowerLimits,
                                                const blVectorType& angularMotionUpperLimits)
{
    setRestitutionCoefficients(restitutionCoefficients);
    setAngularRestitutionCoefficients(angularRestitutionCoefficients);
    setIsMotionLimited(isMotionLimited);
    setIsAngularMotionLimited(isAngularMotionLimited);
    setMotionLimits(motionLowerLimits,motionUpperLimits);
    setAngularMotionLimits(angularMotionLowerLimits,angularMotionUpperLimits);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blRestitution<blDataType>::blRestitution(const blRestitution<blDataType>& restitution)
{
    // Copy the restitution coefficients
    setRestitutionCoefficients(restitution.getRestitutionCoefficients());
    setAngularRestitutionCoefficients(restitution.getAngularRestitutionCoefficients());
    setIsMotionLimited(restitution.getIsMotionLimited());
    setIsAngularMotionLimited(restitution.getIsAngularMotionLimited());
    setMotionLimits(restitution.getMotionLowerLimits(),restitution.getMotionUpperLimits());
    setAngularMotionLimits(restitution.getAngularMotionLowerLimits(),restitution.getAngularMotionUpperLimits());
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const typename blRestitution<blDataType>::blVectorBool& blRestitution<blDataType>::getIsMotionLimited()const
{
    return m_isMotionLimited;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const typename blRestitution<blDataType>::blVectorBool& blRestitution<blDataType>::getIsAngularMotionLimited()const
{
    return m_isAngularMotionLimited;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRestitution<blDataType>::setMotionLimits(const blVectorType& motionLowerLimits,
                                                       const blVectorType& motionUpperLimits)
{
    // We'll make sure that the
    // motion limits are ordered

    if(motionLowerLimits.x() <= motionUpperLimits.x())
    {
        m_motionLowerLimits.x() = motionLowerLimits.x();
        m_motionUpperLimits.x() = motionUpperLimits.x();
    }
    else
    {
        m_motionLowerLimits.x() = motionUpperLimits.x();
        m_motionUpperLimits.x() = motionLowerLimits.x();
    }
    if(motionLowerLimits.y() <= motionUpperLimits.y())
    {
        m_motionLowerLimits.y() = motionLowerLimits.y();
        m_motionUpperLimits.y() = motionUpperLimits.y();
    }
    else
    {
        m_motionLowerLimits.y() = motionUpperLimits.y();
        m_motionUpperLimits.y() = motionLowerLimits.y();
    }
    if(motionLowerLimits.z() <= motionUpperLimits.z())
    {
        m_motionLowerLimits.z() = motionLowerLimits.z();
        m_motionUpperLimits.z() = motionUpperLimits.z();
    }
    else
    {
        m_motionLowerLimits.z() = motionUpperLimits.z();
        m_motionUpperLimits.z() = motionLowerLimits.z();
    }
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRestitution<blDataType>::setAngularMotionLimits(const blVectorType& angularMotionLowerLimits,
                                                              const blVectorType& angularMotionUpperLimits)
{
    // We'll make sure
    // that the angular
    // motion limits are
    // ordered

    if(angularMotionLowerLimits.x() <= angularMotionUpperLimits.x())
    {
        m_angularMotionLowerLimits.x() = angularMotionLowerLimits.x();
        m_angularMotionUpperLimits.x() = angularMotionUpperLimits.x();
    }
    else
    {
        m_angularMotionLowerLimits.x() = angularMotionUpperLimits.x();
        m_angularMotionUpperLimits.x() = angularMotionLowerLimits.x();
    }
    if(angularMotionLowerLimits.y() <= angularMotionUpperLimits.y())
    {
        m_angularMotionLowerLimits.y() = angularMotionLowerLimits.y();
        m_angularMotionUpperLimits.y() = angularMotionUpperLimits.y();
    }
    else
    {
        m_angularMotionLowerLimits.y() = angularMotionUpperLimits.y();
        m_angularMotionUpperLimits.y() = angularMotionLowerLimits.y();
    }
    if(angularMotionLowerLimits.z() <= angularMotionUpperLimits.z())
    {
        m_angularMotionLowerLimits.z() = angularMotionLowerLimits.z();
        m_angularMotionUpperLimits.z() = angularMotionUpperLimits.z();
    }
    else
    {
        m_angularMotionLowerLimits.z() = angularMotionUpperLimits.z();
        m_angularMotionUpperLimits.z() = angularMotionLowerLimits.z();
    }
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const typename blRestitution<blDataType>::blVectorType& blRestitution<blDataType>::getMotionLowerLimits()const
{
    return m_motionLowerLimits;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const typename blRestitution<blDataType>::blVectorType& blRestitution<blDataType>::getMotionUpperLimits()const
{
    return m_motionUpperLimits;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const typename blRestitution<blDataType>::blVectorType& blRestitution<blDataType>::getAngularMotionLowerLimits()const
{
    return m_angularMotionLowerLimits;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const typename blRestitution<blDataType>::blVectorType& blRestitution<blDataType>::getAngularMotionUpperLimits()const
{
    return m_angularMotionUpperLimits;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRestitution<blDataType>::setRestitutionCoefficients(const blDataType& xCoeff,
                                                                  const blDataType& yCoeff,
                                                                  const blDataType& zCoeff)
{
    m_restitutionCoefficients.x() = xCoeff;
    m_restitutionCoefficients.y() = yCoeff;
    m_restitutionCoefficients.z() = zCoeff;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRestitution<blDataType>::setRestitutionCoefficients(const blVectorType& restitutionCoefficients)
{
    m_restitutionCoefficients = restitutionCoefficients;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const typename blRestitution<blDataType>::blVectorType& blRestitution<blDataType>::getRestitutionCoefficients()const
{
    return m_restitutionCoefficients;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRestitution<blDataType>::setAngularRestitutionCoefficients(const blDataType& xCoeff,
                                                                         const blDataType& yCoeff,
                                                                         const blDataType& zCoeff)
{
    m_angularRestitutionCoefficients.x() = xCoeff;
    m_angularRestitutionCoefficients.y() = yCoeff;
    m_angularRestitutionCoefficients.z() = zCoeff;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRestitution<blDataType>::setAngularRestitutionCoefficients(const blVectorType& angularRestitutionCoefficients)
{
    m_angularRestitutionCoefficients = angularRestitutionCoefficients;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const typename blRestitution<blDataType>::blVectorType& blRestitution<blDataType>::getAngularRestitutionCoefficients()const
{
    return m_angularRestitutionCoefficients;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRestitution<blDataType>::setIsMotionLimited(const blVectorBool& isMotionLimited)
{
    m_isMotionLimited = isMotionLimited;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRestitution<blDataType>::setIsMotionLimited(const bool& isXMotionLimited,
                                                          const bool& isYMotionLimited,
                                                          const bool& isZMotionLimited)
{
    m_isMotionLimited.x() = isXMotionLimited;
    m_isMotionLimited.y() = isYMotionLimited;
    m_isMotionLimited.z() = isZMotionLimited;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRestitution<blDataType>::setIsAngularMotionLimited(const blVectorBool& isAngularMotionLimited)
{
    m_isAngularMotionLimited = isAngularMotionLimited;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRestitution<blDataType>::setIsAngularMotionLimited(const bool& isXAngularMotionLimited,
                                                                 const bool& isYAngularMotionLimited,
                                                                 const bool& isZAngularMotionLimited)
{
    m_isAngularMotionLimited.x() = isXAngularMotionLimited;
    m_isAngularMotionLimited.y() = isYAngularMotionLimited;
    m_isAngularMotionLimited.z() = isZAngularMotionLimited;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRestitution<blDataType>::resolveMotionLimits()
{
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRestitution<blDataType>::resolveAngularMotionLimits()
{
}
//-------------------------------------------------------------------


#endif // BL_RESTITUTION_HPP
