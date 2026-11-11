// swift-tools-version: 6.0
import PackageDescription
let package = Package(
 name: "COBackend",
 platforms: [.macOS(.v13)],
 products: [.library(name: "COBackendCore", targets: ["COBackendCore"]), .executable(name: "co-server", targets: ["COBackendServer"])],
 dependencies: [.package(url: "https://github.com/vapor/vapor.git", from: "4.110.0")],
 targets: [
  .target(name: "COBackendCore", dependencies: [.product(name: "Vapor", package: "vapor")]),
  .executableTarget(name: "COBackendServer", dependencies: ["COBackendCore", .product(name: "Vapor", package: "vapor")]),
  .testTarget(name: "COBackendCoreTests", dependencies: ["COBackendCore"])
 ],
 swiftLanguageModes: [.v6]
)
