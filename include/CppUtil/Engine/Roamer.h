#ifndef _ENGINE_VIEWER_ROAMER_H_
#define _ENGINE_VIEWER_ROAMER_H_

#include <CppUtil/Basic/HeapObj.h>

namespace CppUtil {
	namespace QT {
		class RawAPI_OGLW;
	}

	namespace OpenGL {
		class Camera;
	}

	namespace Engine {
		class Roamer : public Basic::HeapObj {
			HEAP_OBJ_SETUP(Roamer)
		public:
			Roamer(QT::RawAPI_OGLW * pOGLW);

			void Init();
			void SetWH(int w, int h);

			QT::RawAPI_OGLW * GetOGLW() { return pOGLW; }
			Basic::Ptr<OpenGL::Camera> GetCamera() { return camera; }

		public:
			void SetLock(bool isLock) { lock = isLock; }

		private:
			void ListenerInit();
			void UpdateCamera();

			QT::RawAPI_OGLW * pOGLW;
			unsigned int cameraUBO;
			Basic::Ptr<OpenGL::Camera> camera;
			bool lock;
		};
	}
}

#endif//!_ENGINE_VIEWER_ROAMER_H_
