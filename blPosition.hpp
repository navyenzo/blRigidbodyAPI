#ifndef BL_POSITION_HPP
#define BL_POSITION_HPP


//-------------------------------------------------------------------
// FILE:            blPosition.hpp
// CLASS:           blPosition
// BASE CLASS:      None
//
// PURPOSE:         A base class to add
//                  position to an object
//                  together with the
//                  ability to translate
//                  the object
//
// AUTHOR:          Vincenzo Barbato
//                  http://www.barbatolabs.com
//                  navyenzo@gmail.com
//
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
//
// DEPENDENCIES:    blMathAPI::blVector3d -- From the blMathAPI used to
//                                           represent the position
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
class blPosition
{
protected: // Protected typedefs

    typedef blMathAPI::blVector3d<blDataType>       blVectorType;

public: // Constructors and destructors

    // Default constructor

    blPosition(const blDataType& xPos = 0,
               const blDataType& yPos = 0,
               const blDataType& zPos = 0);

    // Constructor from
    // a vector

    blPosition(const blVectorType& position);

    // Copy constructor
    // (from a different
    // type position)

    template<typename blDataType2>
    blPosition(const blPosition<blDataType2>& position);

    // Destructor
    ~blPosition()
    {
    }

public: // Public functions

    // Functions used to
    // get the position

    const blVectorType&                             getPosition()const;
    const blVectorType&                             getEarlierPosition()const;
    const blVectorType&                             getStartingPosition()const;

    // Function used to
    // get the total
    // movement from
    // the starting
    // position to
    // the current
    // position

    const blVectorType                              calculateMovement()const;

    // Function used to
    // set the position
    // using a vector

    void                                            setPosition(const blVectorType& position);

    // Funtion used to
    // set the position
    // using three values

    void                                            setPosition(const blDataType& xPos,
                                                                const blDataType& yPos,
                                                                const blDataType& zPos);

    // Function used to
    // translate using
    // a vector

    void                                            translate(const blVectorType& translationVector);

    // Function used to
    // translate using
    // Sthree values

    virtual void                                    translate(const blDataType& xStep,
                                                              const blDataType& yStep,
                                                              const blDataType& zStep);

private:// Private variables

    // The position
    // vector

    blVectorType                                    m_position;

    // The earlier
    // position vector

    blVectorType                                    m_earlierPosition;

    // The position
    // this rigid
    // body started
    // at

    blVectorType                                    m_startingPosition;
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blPosition<blDataType>::blPosition(const blDataType& xPos,
                                          const blDataType& yPos,
                                          const blDataType& zPos)
{
    setPosition(xPos,yPos,zPos);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blPosition<blDataType>::blPosition(const blVectorType& position)
{
    setPosition(position);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<typename blDataType2>
inline blPosition<blDataType>::blPosition(const blPosition<blDataType2>& position)
{
    m_position = position.getPosition();
    m_earlierPosition = position.getEarlierPosition();
    m_startingPosition = position.getStartingPosition();
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const typename blPosition<blDataType>::blVectorType blPosition<blDataType>::calculateMovement()const
{
    return (m_position - m_startingPosition);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const typename blPosition<blDataType>::blVectorType& blPosition<blDataType>::getPosition()const
{
    return m_position;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const typename blPosition<blDataType>::blVectorType& blPosition<blDataType>::getEarlierPosition()const
{
    return m_earlierPosition;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const typename blPosition<blDataType>::blVectorType& blPosition<blDataType>::getStartingPosition()const
{
    return m_startingPosition;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blPosition<blDataType>::setPosition(const blVectorType& position)
{
    setPosition(position.x,
                position.y,
                position.z);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blPosition<blDataType>::setPosition(const blDataType& xPos,
                                                const blDataType& yPos,
                                                const blDataType& zPos)
{
    // Set the position
    // components

    m_position.x = xPos;
    m_position.y = yPos;
    m_position.z = zPos;

    // Since we're
    // explicitly
    // setting the
    // position, we
    // also set it
    // as the earlier
    // position

    m_earlierPosition = m_position;

    // We also store
    // the passed
    // position as
    // the starting
    // position

    m_startingPosition = m_position;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blPosition<blDataType>::translate(const blVectorType& translationVector)
{
    translate(translationVector.x,
              translationVector.y,
              translationVector.z);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blPosition<blDataType>::translate(const blDataType& xStep,
                                              const blDataType& yStep,
                                              const blDataType& zStep)
{
    // We store the
    // current position

    m_earlierPosition = m_position;

    // Add the translation
    // vector to the
    // current object's
    // position

    m_position.x += xStep;
    m_position.y += yStep;
    m_position.z += zStep;
}
//-------------------------------------------------------------------


#endif // BL_POSITION_HPP
