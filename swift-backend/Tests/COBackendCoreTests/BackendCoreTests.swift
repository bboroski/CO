import Testing
@testable import COBackendCore
@Test func validConfiguration() throws {
 let c=try AppConfig(serviceName:"test",version:"1.0",hostname:"127.0.0.1",port:8080)
 #expect(c.port == 8080)
}
@Test func invalidPortRejected() {
 #expect(throws:BackendConfigurationError.invalidValue("PORT")) {
  try AppConfig(serviceName:"test",version:"1",hostname:"localhost",port:70000)
 }
}
@Test func environmentConfiguration() throws {
 let c=try AppConfig.load(environment:["PORT":"9090","HOST":"127.0.0.1"],defaultServiceName:"test")
 #expect(c.port == 9090)
}
