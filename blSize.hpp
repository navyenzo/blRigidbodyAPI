#ifndef BL_SIZE_HPP
#define BL_SIZE_HPP


//-------------------------------------------------------------------
// FILE:            blSize.hpp
// CLASS:           blSize
// BASE CLASS:      None
//
// PURPOSE:         A base class to add a size to an object with
//                  the ability to scale the object
//
// AUTHOR:          Vincenzo Barbato
//                  http://www.barbatolabs.com
//                  navyenzo@gmail.com
//
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
//
// DEPENDENCIES:    blMathAPI::blVector3d -- From the blMathAPI used to
//                                           represent the size
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
class blSize
{
protected: // Protected typedefs

    typedef blMathAPI::blVector3d<blDataType>                   blVectorType;

public: // Constructors and destructors

    // Default constructor

    blSize(const blDataType& x = 1,
           const blDataType& y = 1,
           const blDataType& z = 1);

    // Constructor from a vector

    blSize(const blVectorType& size);

    // Copy constructor

    blSize(const blSize<blDataType>& size);

    // Destructor

    ~blSize()
    {
    }

public: // Public functions

    // Functions used to
    // get object's size

    const blVectorType&                                         getSize()const;

    // Function used to
    // set the object's
    // size

    void                                                        setSize(const blVectorType& size);
    void                                                        setSize(const blDataType& x,
                                                                        const blDataType& y,
                                                                        const blDataType& z);

    // Function used to
    // scale the object

    void                                                        scale(const blVectorType& scaleVector);
    void                                                        scale(const blDataType& xScale,
                                                                      const blDataType& yScale,
                                                                      const blDataType& zScale);

    // Function used to
    // increase or decrease
    // the size

    void                                                        changeSize(const blVectorType& changeVector);
    void                                                        changeSize(const blDataType& xChange,
                                                                           const blDataType& yChange,
                                                                           const blDataType& zChange);

protected: // Private variables

    // The size

    blVectorType                                                m_size;
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blSize<blDataType>::blSize(const blDataType& x,
                                  const blDataType& y,
                                  const blDataType& z)
{
    this->setSize(x,y,z);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blSize<blDataType>::blSize(const blVectorType& size)
{
    this->setSize(size);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blSize<blDataType>::blSize(const blSize<blDataType>& size)
{
    this->setSize(size.getSize());
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blSize<blDataType>::setSize(const blDataType& x,
                                        const blDataType& y,
                                        const blDataType& z)
{
    m_size.x = x;
    m_size.y = y;
    m_size.z = z;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blSize<blDataType>::setSize(const blVectorType& size)
{
    m_size = size;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const typename blSize<blDataType>::blVectorType& blSize<blDataType>::getSize()const
{
    return m_size;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blSize<blDataType>::scale(const blVectorType& scaleVector)
{
    m_size.x *= scaleVector.x;
    m_size.y *= scaleVector.y;
    m_size.z *= scaleVector.z;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blSize<blDataType>::scale(const blDataType& xScale,
                                      const blDataType& yScale,
                                      const blDataType& zScale)
{
    m_size.x *= xScale;
    m_size.y *= yScale;
    m_size.z *= zScale;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blSize<blDataType>::changeSize(const blVectorType& changeVector)
{
    m_size += changeVector;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blSize<blDataType>::changeSize(const blDataType& xChange,
                                           const blDataType& yChange,
                                           const blDataType& zChange)
{
    m_size.x += xChange;
    m_size.y += yChange;
    m_size.z += zChange;
}
//-------------------------------------------------------------------


#endif // BL_SIZE_HPP
