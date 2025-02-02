const fs = require('fs');
const path = require('path');

function deleteFilesInDir(dir) {
  fs.readdir(dir, (err, files) => {
    if (err) {
      console.error(`Error reading directory ${dir}:`, err);
      return;
    }

    files.forEach(file => {
      const filePath = path.join(dir, file);
      fs.stat(filePath, (err, stats) => {
        if (err) {
          console.error(`Error getting stats of file ${filePath}:`, err);
          return;
        }

        if (stats.isDirectory()) {
          // Recursively process nested directories
          deleteFilesInDir(filePath);
        } else if (stats.isFile() && ['.exe', '.o'].includes(path.extname(file).toLowerCase())) {
          // Delete matching files
          fs.unlink(filePath, err => {
            if (err) {
              console.error(`Error deleting file ${filePath}:`, err);
            } else {
              console.log(`Deleted: ${filePath}`);
            }
          });
        }
      });
    });
  });
}

// Change the directory path as needed
const targetDir = path.resolve(__dirname, '/Users/vishnukumar/DSA-prac');
deleteFilesInDir(targetDir);
