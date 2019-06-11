/**********************************************************************

  Audacity: A Digital Audio Editor

  EnvelopeEditor.h

  Paul Licameli split this from Envelope.h

**********************************************************************/

#ifndef __AUDACITY_ENVELOPE_EDITOR__
#define __AUDACITY_ENVELOPE_EDITOR__

class wxMouseEvent;
class wxRect;
class Envelope;
class TrackPanelDrawingContext;
class ZoomInfo;

// A class that holds state for the duration of dragging
// of an envelope point.
class EnvelopeEditor
{
public:
   static void DrawPoints(
      const Envelope &env,
      TrackPanelDrawingContext &context,
      const wxRect & r,
      bool dB, double dBRange,
      float zoomMin, float zoomMax, bool mirrored);

   /** \brief Get many envelope points for pixel columns at once,
    * but don't assume uniform time per pixel.
   */
   static void GetValues
      ( const Envelope &env,
        double aligned_time, double sampleDur,
        double *buffer, int bufferLen, int leftOffset,
        const ZoomInfo &zoomInfo);

   EnvelopeEditor(Envelope &envelope, bool mirrored);
   ~EnvelopeEditor();

   // Event Handlers
   // Each of these returns true if the envelope needs to be redrawn
   bool MouseEvent(const wxMouseEvent & event, wxRect & r,
      const ZoomInfo &zoomInfo, bool dB, double dBRange,
      float zoomMin = -1.0, float zoomMax = 1.0);

private:
   bool HandleMouseButtonDown(const wxMouseEvent & event, wxRect & r,
      const ZoomInfo &zoomInfo, bool dB, double dBRange,
      float zoomMin = -1.0, float zoomMax = 1.0);
   bool HandleDragging(const wxMouseEvent & event, wxRect & r,
      const ZoomInfo &zoomInfo, bool dB, double dBRange,
      float zoomMin = -1.0, float zoomMax = 1.0, float eMin = 0., float eMax = 2.);
   bool HandleMouseButtonUp();

private:
   float ValueOfPixel(int y, int height, bool upper,
      bool dB, double dBRange,
      float zoomMin, float zoomMax);
   void MoveDragPoint(const wxMouseEvent & event, wxRect & r,
      const ZoomInfo &zoomInfo, bool dB, double dBRange,
      float zoomMin, float zoomMax);

   Envelope &mEnvelope;
   const bool mMirrored;

   /** \brief Number of pixels contour is from the true envelope. */
   int mContourOffset;

   // double mInitialVal;

   // int mInitialY;
   bool mUpper;
   int mButton;
   bool mDirty;
};


#endif
