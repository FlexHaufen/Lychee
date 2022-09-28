#include <Lychee/Lychee.h>
//#include "EditorLayer.h"

namespace Lychee {

	class LycheeApp : public Core {
	public:
		LycheeApp()
			: Core() {
            
			//PushLayer(new EditorLayer());
		}   
	};

	Core* CreateApplication() {
		return new LycheeApp();
	}

}
