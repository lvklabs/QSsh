import qbs

Project {
    name: "Libs"
    references: [        
        "ssh/ssh.qbs"
    ].concat(project.additionalLibs)
}
