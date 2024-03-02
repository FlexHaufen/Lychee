#include <Lychee/Lychee.h>

#include "EditorLayer.h"

namespace Lychee {

	class LycheeApp : public Core {
	public:
		LycheeApp()
			: Core() {
            
			LY_INFO("Starting Lychee App");
			PushLayer(new EditorLayer());
		}   
	};
}
