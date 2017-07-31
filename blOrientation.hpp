#ifndef BL_ORIENTATION_HPP
#define BL_ORIENTATION_HPP


//-------------------------------------------------------------------
// FILE:            blOrientation.hpp
// CLASS:           blOrientation
// BASE CLASS:      None
//
// PURPOSE:         A base class to add orientation to an object
//                  with the ability to rotate the object, and
//                  determine its three x,y,z coordinate axes
//                  and its rotation angle/axis
//
// AUTHOR:          Vincenzo Barbato
//                  http://www.barbatolabs.com
//                  navyenzo@gmail.com
//
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
//
// DEPENDENCIES:    blMathAPI::blVector3d -- From the blMathAPI used to
//                                represent its axis of rotation
//                                and its orientation axes
//                  blMathAPI::blQuaternion -- From the blMathAPI used to
//                                  represent rotation orientation
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
class blOrientation
{
protected: // Protected typedefs

    typedef blMathAPI::blVector3d<blDataType>                   blVectorType;
    typedef blMathAPI::blQuaternion<blDataType>                 blQuaternionType;

public: // Constructors and destructors

    // Default constructor
    blOrientation(const blVectorType& xAxis = blVectorType(1,0,0),
                  const blVectorType& yAxis = blVectorType(0,1,0));

    // Copy constructor
    blOrientation(const blOrientation<blDataType>& orientation);

    // Destructor
    ~blOrientation(void)
    {
    }

public: // Public functions

    // Function used to
    // set the orientation
    // using an x-axis
    // and a y-axis

    void                                                        setOrientationWithTwoAxes(const blVectorType& xAxis,
                                                                                          const blVectorType& yAxis);

    // Function used to
    // set the orientation
    // using the total
    // rotataion quaternion

    void                                                        setOrientation(const blQuaternionType& rotQtn);

    // Function used to
    // set the orientation
    // using three Euler
    // Angles

    void                                                        setOrientationWithEulerAngles(const blDataType& xAngle,
                                                                                              const blDataType& yAngle,
                                                                                              const blDataType& zAngle);

    // Function used to
    // rotate the body
    // using a quaternion

    virtual void                                                rotate(const blQuaternionType& rotQtn,
                                                                       const bool& shouldOrientationAxesBeUpdated = true,
                                                                       const bool& shouldOrientationAngleAndAxisBeUpdated = true);

    // Function used to
    // rotate the object
    // using three Euler
    // Angles

    void                                                        rotateWithEulerAngles(const blDataType& xAngle,
                                                                                      const blDataType& yAngle,
                                                                                      const blDataType& zAngle,
                                                                                      const bool& shouldOrientationAxesBeUpdated = true,
                                                                                      const bool& shouldOrientationAngleAndAxisBeUpdated = true);

    // Function used to
    // rotate the object
    // using an angle of
    // rotation and an
    // axis of rotation

    void                                                        rotateWithAngleAxis(const blDataType& AngleOfRotation,
                                                                                    const blVectorType& AxisOfRotation,
                                                                                    const bool& shouldOrientationAxesBeUpdated = true,
                                                                                    const bool& shouldOrientationAngleAndAxisBeUpdated = true);

    // Functions used to
    // rotate the object
    // using an angle of
    // rotation and the
    // three components
    // of an axis of rotation

    void                                                        rotateWithAngleAxis(const blDataType& AngleOfRotation,
                                                                                    const blDataType& x,
                                                                                    const blDataType& y,
                                                                                    const blDataType& z,
                                                                                    const bool& shouldOrientationAxesBeUpdated = true,
                                                                                    const bool& shouldOrientationAngleAndAxisBeUpdated = true);

    // Function used to
    // adjust the orientation
    // using total euler
    // angles

    void                                                        adjustOrientation(const blVectorType& TotalEulerAngles,
                                                                                  const bool& shouldOrientationAxesBeUpdated = true,
                                                                                  const bool& shouldOrientationAngleAndAxisBeUpdated = true);

    // Functions used to
    // get the orientation
    // axes of this object's
    // current orientation

    const blVectorType&                                         getxAxis()const;
    const blVectorType&                                         getyAxis()const;
    const blVectorType&                                         getzAxis()const;

    // Functions used to
    // get the angle/axis
    // and quaternion
    // representing the
    // object's current
    // rotation

    const blDataType&                                           getAngleOfRotation()const;
    const blVectorType&                                         getAxisOfRotation()const;
    const blQuaternionType&                                     getRotQtn()const;
    const blQuaternionType&                                     getLastRotQtn()const;
    const blQuaternionType&                                     getEarlierRotQtn()const;
    const blQuaternionType&                                     getStartingRotQtn()const;
    const blVectorType&                                         getTotalEulerAngles()const;
    const blVectorType&                                         getEarlierTotalEulerAngles()const;

    // Function used to
    // update the object's
    // current x,y,z
    // coordinate axes

    void                                                        updateOrientationAxes();

    // Function used to
    // update the object's
    // current orientation
    // angle/axis of rotation

    void                                                        updateOrientationAngleAndAxisOfRotation();

    // Function used to
    // update the object's
    // total euler angles
    // from the starting
    // rotation

    void                                                        updateTotalEulerAngles();

    // Function used to
    // reset the total
    // euler angles

    void                                                        resetTotalEulerAngles();

private: // Private Variables

    // The object's
    // coordinate axes

    blVectorType                                                m_xAxis;
    blVectorType                                                m_yAxis;
    blVectorType                                                m_zAxis;

    // Rotation angle
    // and axis for the
    // current orientation

    blDataType                                                  m_angleOfRotation;
    blVectorType                                                m_axisOfRotation;

    // Rotation quaternion
    // used to rotate and
    // store the object's
    // current orientation

    blQuaternionType                                            m_rotQtn;
    blQuaternionType                                            m_earlierRotQtn;
    blQuaternionType                                            m_lastRotQtn;
    blQuaternionType                                            m_startingRotQtn;

    // Total rotation
    // euler angles
    // since the
    // starting rotation

    blVectorType                                                m_totalEulerAngles;
    blVectorType                                                m_earlierTotalEulerAngles;
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blOrientation<blDataType>::blOrientation(const blVectorType& xAxis,
                                                const blVectorType& yAxis)
{
    setOrientationWithTwoAxes(xAxis,yAxis);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blOrientation<blDataType>::blOrientation(const blOrientation<blDataType>& orientation)
{
    // Get and store
    // the orientation axes

    m_xAxis = orientation.getxAxis();
    m_yAxis = orientation.getyAxis();
    m_zAxis = orientation.getzAxis();

    // Get and store the
    // rotation angle/axis
    // and quaternion

    m_angleOfRotation = orientation.getAngleOfRotation();
    m_axisOfRotation = orientation.getAxisOfRotation();
    m_rotQtn = orientation.getRotQtn();
    m_lastRotQtn = orientation.getLastRotQtn();
    m_earlierRotQtn = orientation.getEarlierRotQtn();
    m_startingRotQtn = orientation.getStartingRotQtn();
    m_totalEulerAngles = orientation.getTotalEulerAngles();
    m_earlierTotalEulerAngles = orientation.getEarlierTotalEulerAngles();
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blOrientation<blDataType>::setOrientationWithTwoAxes(const blVectorType& xAxis,
                                                                 const blVectorType& yAxis)
{
    // First:       Normalize and store
    //              the passed x and y axes

    m_xAxis = xAxis.getNormalized();
    m_yAxis = yAxis.getNormalized();

    // Second:      Calculate the z
    //              axis and store it

    m_zAxis = crossProduct(m_xAxis,m_yAxis).getNormalized();

    // Third:       Calculate an angle/axis
    //              of rotation that rotates
    //              the object's x axis so that
    //              it lies on the specified x axis

    blVectorType xxAxis(1,0,0);
    m_angleOfRotation = -std::acos(xxAxis*m_xAxis);
    m_axisOfRotation = crossProduct(m_xAxis,xxAxis);
    m_axisOfRotation.normalize();

    // Fourth:      Store this temporary
    //              rotation in the object's
    //              rotation quaternion

    m_rotQtn = blQuaternionType(m_angleOfRotation,
                                m_axisOfRotation.x,
                                m_axisOfRotation.y,
                                m_axisOfRotation.z);

    // Fifth:       Calculate the
    //              temporary
    //              rotated y axis

    blVectorType yyAxis = blVectorType(0,1,0);
    m_rotQtn.rotateVector(yyAxis);

    // Sixth:       Calculate an angle/axis
    //              of rotation that rotates
    //              the object's temporary
    //              rotated y axis so that it
    //              lies on the specified y axis

    m_angleOfRotation = -std::acos(yyAxis*m_yAxis);
    m_axisOfRotation = crossProduct(m_yAxis,yyAxis);
    if(m_axisOfRotation.getMagnitude() > 0)
        m_axisOfRotation.normalize();

    // Seventh:     Store this last
    //              rotation in the
    //              object's rotation
    //              quaternion

    m_rotQtn = blQuaternionType(m_angleOfRotation,
                                m_axisOfRotation.x,
                                m_axisOfRotation.y,
                                m_axisOfRotation.z) * m_rotQtn;

    // Store the current
    // rotation quaternion
    // also as the earlier
    // rotation quaternion
    // and as the starting
    // quaternion

    m_lastRotQtn = blQuaternionType(0,1,0,0);
    m_earlierRotQtn = m_rotQtn;
    m_startingRotQtn = m_rotQtn;

    // We zero out the
    // total euler angles

    resetTotalEulerAngles();

    updateOrientationAngleAndAxisOfRotation();
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blOrientation<blDataType>::setOrientation(const blQuaternionType& rotQtn)
{
    // We store the
    // quaternion

    m_rotQtn = rotQtn;
    m_lastRotQtn = blQuaternionType(0,1,0,0);
    m_earlierRotQtn = m_rotQtn;
    m_startingRotQtn = m_rotQtn;

    // Update the axis
    // and angle of rotation
    // and the coordinate
    // axes

    updateOrientationAxes();
    updateOrientationAngleAndAxisOfRotation();

    // We zero out the
    // total euler angles

    resetTotalEulerAngles();
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blOrientation<blDataType>::setOrientationWithEulerAngles(const blDataType& xAngle,
                                                                     const blDataType& yAngle,
                                                                     const blDataType& zAngle)
{
    // First we set
    // the orientation
    // forming a quaternion
    // form the euler
    // angles

    setOrientation(blQuaternionType(xAngle,yAngle,zAngle));

    // Then we manually
    // set the total
    // euler angles to
    // match the passed
    // angles, since the
    // setOrientation function
    // has calculated
    // its own euler angles
    // from its current
    // rotation

    m_totalEulerAngles.x = xAngle;
    m_totalEulerAngles.y = yAngle;
    m_totalEulerAngles.z = zAngle;

    m_earlierTotalEulerAngles = m_totalEulerAngles;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blOrientation<blDataType>::rotate(const blQuaternionType& rotQtn,
                                              const bool& shouldOrientationAxesBeUpdated,
                                              const bool& shouldOrientationAngleAndAxisBeUpdated)
{
    // First:       Store the current
    //              rotation

    m_lastRotQtn = rotQtn;

    m_earlierRotQtn = m_rotQtn;

    // Second:      Store the rotation
    //              in the object's
    //              total rotation
    //              quaternion but
    //              check to make sure
    //              that we had a rotation
    //              in the first place

    if(m_rotQtn.m_w == 1)
        m_rotQtn = rotQtn;
    else
        m_rotQtn = rotQtn*m_rotQtn;

    // Third:       Update the
    //              orientation
    //              axes

    if(shouldOrientationAxesBeUpdated)
        updateOrientationAxes();

    // Fourth:      Update the angle
    //              axis of rotation

    if(shouldOrientationAngleAndAxisBeUpdated)
        updateOrientationAngleAndAxisOfRotation();

    // Fifth:       Update the total
    //              euler angles

    updateTotalEulerAngles();
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blOrientation<blDataType>::rotateWithEulerAngles(const blDataType& xAngle,
                                                             const blDataType& yAngle,
                                                             const blDataType& zAngle,
                                                             const bool& shouldOrientationAxesBeUpdated,
                                                             const bool& shouldOrientationAngleAndAxisBeUpdated)
{
    rotate(blQuaternionType(xAngle,yAngle,zAngle),
           shouldOrientationAxesBeUpdated,
           shouldOrientationAngleAndAxisBeUpdated);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blOrientation<blDataType>::rotateWithAngleAxis(const blDataType& AngleOfRotation,
                                                           const blDataType& x,
                                                           const blDataType& y,
                                                           const blDataType& z,
                                                           const bool& shouldOrientationAxesBeUpdated,
                                                           const bool& shouldOrientationAngleAndAxisBeUpdated)
{
    // Form a quaternion
    // for this rotation

    blQuaternionType rotQtn(AngleOfRotation,x,y,z);

    // rotate using
    // the quaternion

    this->rotate(rotQtn,
                 shouldOrientationAxesBeUpdated,
                 shouldOrientationAngleAndAxisBeUpdated);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blOrientation<blDataType>::rotateWithAngleAxis(const blDataType& AngleOfRotation,
                                                           const blVectorType& AxisOfRotation,
                                                           const bool& shouldOrientationAxesBeUpdated,
                                                           const bool& shouldOrientationAngleAndAxisBeUpdated)
{
    // Form a quaternion
    // for this rotation

    blQuaternionType rotQtn(AngleOfRotation,
                            AxisOfRotation.x,
                            AxisOfRotation.y,
                            AxisOfRotation.z);

    // rotate using
    // the quaternion

    this->rotate(rotQtn,
                 shouldOrientationAxesBeUpdated,
                 shouldOrientationAngleAndAxisBeUpdated);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blOrientation<blDataType>::adjustOrientation(const blVectorType& TotalEulerAngles,
                                                         const bool& shouldOrientationAxesBeUpdated,
                                                         const bool& shouldOrientationAngleAndAxisBeUpdated)
{
    // Form a quaternion
    // for this rotation

    m_rotQtn = blQuaternionType(TotalEulerAngles.x,
                                TotalEulerAngles.y,
                                TotalEulerAngles.z);

    m_lastRotQtn = blQuaternionType(0,1,0,0);
    m_earlierRotQtn = m_rotQtn;
    m_startingRotQtn = m_rotQtn;

    // Now we update the
    // total euler angles

    m_earlierTotalEulerAngles = m_totalEulerAngles;
    m_totalEulerAngles = TotalEulerAngles;

    // Update the
    // orientation
    // axes

    if(shouldOrientationAxesBeUpdated)
        updateOrientationAxes();

    // Update the
    // orientation
    // angle and
    // axis of rotation

    if(shouldOrientationAngleAndAxisBeUpdated)
        updateOrientationAngleAndAxisOfRotation();
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blOrientation<blDataType>::updateOrientationAxes()
{
    // First:       rotate the object's
    //              orientation axes

    m_xAxis = blVectorType(1,0,0);
    m_yAxis = blVectorType(0,1,0);
    m_rotQtn.rotateVector(m_xAxis);
    m_rotQtn.rotateVector(m_yAxis);

    // Second:      Recalculate the
    //              z axis by crossing
    //              x into y

    m_zAxis = crossProduct(m_xAxis,m_yAxis).getNormalized();
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blOrientation<blDataType>::updateOrientationAngleAndAxisOfRotation()
{
    m_angleOfRotation = m_rotQtn.m_Angle*(blDataType(180)/blMathAPI::pi);
    m_axisOfRotation.x = m_rotQtn.m_Ax;
    m_axisOfRotation.y = m_rotQtn.m_Ay;
    m_axisOfRotation.z = m_rotQtn.m_Az;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blOrientation<blDataType>::updateTotalEulerAngles()
{
    // Get the euler
    // angles for the
    // current and earlier
    // rotations

    blVectorType eulerAngles = m_rotQtn.getEulerAngles();
    blVectorType earlierEulerAngles = m_earlierRotQtn.getEulerAngles();

    // Store the current
    // total euler angles

    m_earlierTotalEulerAngles = m_totalEulerAngles;

    // Add the difference
    // to the total euler
    // angles, but we
    // have to be careful
    // about sign changes
    // that happen everytime
    // the rotation goes
    // from PI to -PI or
    // viceversa



    if(eulerAngles.x * earlierEulerAngles.x > 0)
        m_totalEulerAngles.x += (eulerAngles.x - earlierEulerAngles.x);
    else
    {
        if(eulerAngles.x < -blMathAPI::pi/2.0)
            m_totalEulerAngles.x += (2.0*blMathAPI::pi + eulerAngles.x) - earlierEulerAngles.x;
        else if(eulerAngles.x < 0)
            m_totalEulerAngles.x += eulerAngles.x - earlierEulerAngles.x;
    }

    if(eulerAngles.y * earlierEulerAngles.y > 0)
        m_totalEulerAngles.y += (eulerAngles.y - earlierEulerAngles.y);
    else
    {
        if(eulerAngles.y < -blMathAPI::pi/2.0)
            m_totalEulerAngles.y += (2.0*blMathAPI::pi + eulerAngles.y) - earlierEulerAngles.y;
        else if(eulerAngles.y < 0)
            m_totalEulerAngles.y += eulerAngles.y - earlierEulerAngles.y;
    }

    if(eulerAngles.z * earlierEulerAngles.z > 0)
        m_totalEulerAngles.z += (eulerAngles.z - earlierEulerAngles.z);
    else
    {
        if(eulerAngles.z < -blMathAPI::pi/2.0)
            m_totalEulerAngles.z += (2.0*blMathAPI::pi + eulerAngles.z) - earlierEulerAngles.z;
        else if(eulerAngles.z < 0)
            m_totalEulerAngles.z += eulerAngles.z - earlierEulerAngles.z;
    }

    if(blMathAPI::isNaN(m_totalEulerAngles.x))
        m_totalEulerAngles.x = 0;

    if(blMathAPI::isNaN(m_totalEulerAngles.y))
        m_totalEulerAngles.y = 0;

    if(blMathAPI::isNaN(m_totalEulerAngles.z))
        m_totalEulerAngles.z = 0;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blOrientation<blDataType>::resetTotalEulerAngles()
{
    // We zero out the
    // total euler angles

    m_totalEulerAngles.x = 0;
    m_totalEulerAngles.y = 0;
    m_totalEulerAngles.z = 0;
    m_earlierTotalEulerAngles = m_totalEulerAngles;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const typename blOrientation<blDataType>::blVectorType& blOrientation<blDataType>::getxAxis()const
{
    return m_xAxis;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const typename blOrientation<blDataType>::blVectorType& blOrientation<blDataType>::getyAxis()const
{
    return m_yAxis;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const typename blOrientation<blDataType>::blVectorType& blOrientation<blDataType>::getzAxis()const
{
    return m_zAxis;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType& blOrientation<blDataType>::getAngleOfRotation()const
{
    return m_angleOfRotation;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const typename blOrientation<blDataType>::blVectorType& blOrientation<blDataType>::getAxisOfRotation()const
{
    return m_axisOfRotation;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const typename blOrientation<blDataType>::blQuaternionType& blOrientation<blDataType>::getRotQtn()const
{
    return m_rotQtn;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const typename blOrientation<blDataType>::blQuaternionType& blOrientation<blDataType>::getLastRotQtn()const
{
    return m_lastRotQtn;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const typename blOrientation<blDataType>::blQuaternionType& blOrientation<blDataType>::getEarlierRotQtn()const
{
    return m_earlierRotQtn;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const typename blOrientation<blDataType>::blQuaternionType& blOrientation<blDataType>::getStartingRotQtn()const
{
    return m_startingRotQtn;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const typename blOrientation<blDataType>::blVectorType& blOrientation<blDataType>::getTotalEulerAngles()const
{
    return m_totalEulerAngles;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const typename blOrientation<blDataType>::blVectorType& blOrientation<blDataType>::getEarlierTotalEulerAngles()const
{
    return m_earlierTotalEulerAngles;
}
//-------------------------------------------------------------------


#endif // BL_ORIENTATION_HPP
