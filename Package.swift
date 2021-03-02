// swift-tools-version:4.0

import PackageDescription

let package = Package(
    name: "cfactorial",
    products: [
        .library(name: "cfactorial", targets: ["cfactorial"]),
    ],
    targets: [
        .target(
            name: "cfactorial",
            path: "./Sources/factorial"
        ),
    ]
)
