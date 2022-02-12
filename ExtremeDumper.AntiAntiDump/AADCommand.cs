namespace ExtremeDumper.AntiAntiDump;

enum AADCommand : uint {
	Invalid,

	Disconnect,
	EnableMultiDomain,
	GetModules,
	GetMetadata,
	// Client -> Server

	Success = ushort.MaxValue + 1,
	Failure,
	UnhandledException,
	// Server -> Client
}
