#ifndef BL_INERTIA_HPP
#define BL_INERTIA_HPP


//-------------------------------------------------------------------
// FILE:            blInertia.hpp
// CLASS:           blInertia
// BASE CLASS:      None
//
// PURPOSE:         A base class to add mass and
//                  rotational inertia to an object
//
// AUTHOR:          Vincenzo Barbato
//                  http://www.barbatolabs.com
//                  navyenzo@gmail.com
//
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
//
// DEPENDENCIES:    blMathAPI::blMatrix3d -- From the blMathAPI used to
//                                           represent rotational inertia
//
// NOTES:
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
class blInertia
{
protected: // Protected typedefs

    typedef blMathAPI::blMatrix3d<blDataType>       blMatrixType;

public: // Constructors and destructors

    // Default constructor

    blInertia(const blDataType& mass = 1,
              const blMatrixType& inertia = blMathAPI::eye3d<blDataType>(1));

    // Copy constructor

    blInertia(const blInertia<blDataType>& inertia);

    // Destructor

    ~blInertia()
    {
    }

public: // Public function

    // Functions used to
    // set/get the mass and
    // the inertia tensor

    const blDataType&                               getMass()const;
    const blMatrixType&                             getInertia()const;
    const blMatrixType&                             getInertiaInverse()const;

    void                                            setMass(const blDataType& mass);
    void                                            setInertia(const blMatrixType& inertia);

private: // Private variables

    // The mass and
    // inertia variables

    blDataType                                      m_mass;
    blMatrixType                                    m_inertia;
    blMatrixType                                    m_inertiaInverse;
};
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename blDataType>
inline blInertia<blDataType>::blInertia(const blDataType& mass,
                                        const blMatrixType& inertia)
{
    // Set the mass
    // and inertia
    setMass(mass);
    setInertia(inertia);
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename blDataType>
inline blInertia<blDataType>::blInertia(const blInertia<blDataType>& inertia)
{
    // Copy the mass
    // and inertia
    setMass(inertia.getMass());
    setInertia(inertia.getInertia());
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename blDataType>
inline void blInertia<blDataType>::setMass(const blDataType& mass)
{
    m_mass = mass;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename blDataType>
inline void blInertia<blDataType>::setInertia(const blMatrixType& inertia)
{
    m_inertia = inertia;

    // Calculate and store
    // the inverse of the
    // inertia matrix

    m_inertiaInverse = inv(m_inertia);
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename blDataType>
inline const blDataType& blInertia<blDataType>::getMass()const
{
    return m_mass;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename blDataType>
inline const typename blInertia<blDataType>::blMatrixType& blInertia<blDataType>::getInertia()const
{
    return m_inertia;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename blDataType>
inline const typename blInertia<blDataType>::blMatrixType& blInertia<blDataType>::getInertiaInverse()const
{
    return m_inertiaInverse;
}
//---------------------------------------------------------------------------------------


#endif // BL_INERTIA_HPP
