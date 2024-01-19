#include <Lychee/Lychee.h>
#include "EditorLayer.h"

namespace Lychee {

	class LycheeApp : public Core {
	public:
		LycheeApp()
			: Core(true) {
            
			LY_INFO("Starting Lychee App");
			PushLayer(new EditorLayer());
		}   
	};

	Core* CreateApplication() {
		LY_INFO("Initializing Lychee Application");
		return new LycheeApp();
	}

}
